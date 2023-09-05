#include "psystem.h"

psystem::psystem()
{
    this->buses.push_back(Bus());
}

psystem::addBus(Bus bus)
{
    this->buses.push_back(bus);
    return 0;
}

psystem::getBus(Bus &bus, int index)
{
    if(index < this->buses.size())
    {
        bus = this->buses.begin()[index];
    }
}

psystem::addConn(Connection conn)
{
    conns.push_back(conn);
    return 0;
}

psystem::getConn(Connection &conn, int index)
{
    if(index < conns.size())
    {
        conn = conns.begin()[index];
    }
}

psystem::init_ybus()
{
    ybus.assign(this->buses.size() * this->buses.size(),complex<double>(0,0));
    Connection element;
    for(int i=0; i < conns.size(); i++)
    {
        getConn(element, i);
        ybus[this->buses.size() * element.terminal1 + element.terminal2] = ybus[this->buses.size() * element.terminal1 + element.terminal2] - complex<double>(1,0) / element.Z;
        ybus[this->buses.size() * element.terminal2 + element.terminal1] = ybus[this->buses.size() * element.terminal2 + element.terminal1] - complex<double>(1,0) / element.Z;
        ybus[this->buses.size() * element.terminal1 + element.terminal1] = ybus[this->buses.size() * element.terminal1 + element.terminal1] + complex<double>(1,0) / element.Z;
        ybus[this->buses.size() * element.terminal2 + element.terminal2] = ybus[this->buses.size() * element.terminal2 + element.terminal2] + complex<double>(1,0) / element.Z;
    }
    return 0;
}

psystem::get_ybus_element(complex<double> &element, int i, int j)
{
    element = ybus[i*this->buses.size()+j];
}

psystem::make_pu(double v_base, double s_base, int bus_id)
{
    for(int i=0; i<conns.size(); i++)
    {
        conns[i].donepu = false;
    }
    pu_helper(v_base, s_base, bus_id);
}

psystem::pu_helper(double v_base, double s_base, int bus_id)
{
    if(bus_id >= buses.size() || bus_id <= 0)
    {
        return 1;
    }
    if(buses[bus_id].v_base != -1)
    {
        return 2;
    }
    buses[bus_id].make_pu(v_base,s_base);
    for(int i=0; i<conns.size(); i++)
    {
        if(conns[i].donepu)
        {
            continue;
        }
        if(conns[i].terminal1 == bus_id)
        {
            conns[i].make_pu(v_base,s_base);
            pu_helper(v_base * conns[i].K, s_base, conns[i].terminal2);
        }
        else if(conns[i].terminal2 == bus_id)
        {
            conns[i].make_pu(v_base / conns[i].K,s_base);
            pu_helper(v_base / conns[i].K, s_base, conns[i].terminal1);
        }
    }
}

psystem::current_element(complex<double> &I, int bus_id)
{
    complex<double> yb;
    complex<double> current(0,0);
    for(int i=1;i < this->buses.size(); i++){
        get_ybus_element(yb, bus_id, i);
        current += yb * polar(this->buses[i].v,this->buses[i].d);
    }
    I = current;
    return 0;
}

psystem::analyze_powerflow(int iteration)
{
    complex<double> current;
    complex<double> voltage;
    complex<double> yb;
    double e = 0;
    for(int i=1; i < this->buses.size(); i++)
    {
        switch(this->buses[i].type)
        {
        case Bus::PV_BUS:
            current_element(current, i);
            this->buses[i].q = 0;
            this->buses[i].d = 0;
            break;
        case Bus::PQ_BUS:
            this->buses[i].v=1;
            this->buses[i].d=0;
            break;
        case Bus::VD_BUS:
            this->buses[i].p = 0;
            this->buses[i].q = 0;
            break;
        }
    }
    for(;iteration > 0; iteration--)
    {
        for(int i=1; i < this->buses.size(); i++)
        {
            switch(this->buses[i].type)
            {
            case Bus::PV_BUS:
                current_element(current,i);
                get_ybus_element(yb,i,i);
                this->buses[i].q = -imag(conj(polar(this->buses[i].v,this->buses[i].d))*current);
                voltage = (complex<double>(this->buses[i].p,-this->buses[i].q)/conj(polar(this->buses[i].v,this->buses[i].d)) - current + (yb * polar(this->buses[i].v,this->buses[i].d)))/yb;
                e = sqrt(pow(this->buses[i].v,2)-pow(imag(voltage),2));
                voltage = complex<double>(e,imag(voltage));
                this->buses[i].v = abs(voltage);
                this->buses[i].d = atan(imag(voltage)/real(voltage));
                break;
            case Bus::PQ_BUS:
                current_element(current,i);
                get_ybus_element(yb,i,i);
                voltage = (complex<double>(this->buses[i].p,-this->buses[i].q)/conj(polar(this->buses[i].v,this->buses[i].d)) - current + (yb * polar(this->buses[i].v,this->buses[i].d)))/yb;
                this->buses[i].v = abs(voltage);
                this->buses[i].d = atan(imag(voltage)/real(voltage));
                break;
            }
        }
    }
    for(int i =0; i < this->conns.size(); i++){
        this->conns[i].I = (complex<double>(this->buses[this->conns[i].terminal2].v,this->buses[this->conns[i].terminal2].d)-complex<double>(this->buses[this->conns[i].terminal1].v,this->buses[this->conns[i].terminal1].d))/this->conns[i].Z;
    }
}

psystem::~psystem()
{
    //dtor
}

