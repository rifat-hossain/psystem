#include "psystem.h"

psystem::psystem()
{
    this->buses.push_back(Bus());
}

psystem::addBus(Bus bus){
        this->buses.push_back(bus);
        return 0;
    }

    psystem::getBus(Bus &bus, int index){
        if(index < this->buses.size()){
            bus = this->buses.begin()[index];
        }
    }

    psystem::addConn(Connection conn){
        conns.push_back(conn);
        return 0;
    }

    psystem::getConn(Connection &conn, int index){
        if(index < conns.size()){
            conn = conns.begin()[index];
        }
    }

    psystem::init_ybus(){
        ybus.assign(this->buses.size() * this->buses.size(),complex<double>(0,0));
        Connection element;
        for(int i=0; i < conns.size(); i++){
            getConn(element, i);
            ybus[this->buses.size() * element.terminal1 + element.terminal2] = ybus[this->buses.size() * element.terminal1 + element.terminal2] - complex<double>(1,0) / element.Z;
            ybus[this->buses.size() * element.terminal2 + element.terminal1] = ybus[this->buses.size() * element.terminal2 + element.terminal1] - complex<double>(1,0) / element.Z;
            ybus[this->buses.size() * element.terminal1 + element.terminal1] = ybus[this->buses.size() * element.terminal1 + element.terminal1] + complex<double>(1,0) / element.Z;
            ybus[this->buses.size() * element.terminal2 + element.terminal2] = ybus[this->buses.size() * element.terminal2 + element.terminal2] + complex<double>(1,0) / element.Z;
        }
        return 0;
    }

    psystem::get_ybus_element(complex<double> &element, int i, int j){
        element = ybus[i*this->buses.size()+j];
    }

    psystem::make_pu(double v_base, double s_base, int bus_id){
        for(int i=0;i<conns.size();i++){
            conns[i].donepu = false;
        }
        pu_helper(v_base, s_base, bus_id);
    }

    psystem::pu_helper(double v_base, double s_base, int bus_id){
        if(bus_id >= buses.size() || bus_id <= 0){
            return 1;
        }
        if(buses[bus_id].v_base != -1){
            return 2;
        }
        buses[bus_id].make_pu(v_base,s_base);
        for(int i=0;i<conns.size();i++){
            if(conns[i].donepu){
                continue;
            }
            if(conns[i].terminal1 == bus_id){
                conns[i].make_pu(v_base,s_base);
                pu_helper(v_base * conns[i].K, s_base, conns[i].terminal2);
            }
            else if(conns[i].terminal2 == bus_id){
                conns[i].make_pu(v_base / conns[i].K,s_base);
                pu_helper(v_base / conns[i].K, s_base, conns[i].terminal1);
            }
        }
    }

psystem::~psystem()
{
    //dtor
}

