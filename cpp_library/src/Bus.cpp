#include "Bus.h"

Bus::Bus(){}

Bus::Bus(int type, double val1, double val2, bool ispu)
{
    this->v_base = -1;
    this->s_base = -1;
    this->type = type;
    this->ispu = ispu;
    switch(type)
    {
    case Bus::VD_BUS:
        this->v = val1;
        this->d = val2;
        vcom = polar(v,d);
        break;
    case Bus::PQ_BUS:
        this->p = val1;
        this->q = val2;
        break;
    default:
        this->p = val1;
        this->v = val2;
        break;
    }
}

Bus::make_pu(double s_base, double v_base)
{
    if(this->v_base != -1 && this->v_base != v_base)
    {
        return 1;   //Topology error
    }
    this->v_base = v_base;
    this->s_base = s_base;
    if (ispu)
    {
        return 5;   //Already in PU
    }
    ispu = true;
    switch(type)
    {
    case Bus::VD_BUS:
        v = v/v_base;
        break;
    case Bus::PQ_BUS:
        p = p/s_base;
        q = q/s_base;
        v = 1;
        break;
    default:
        p = p/s_base;
        v = v/v_base;
        break;
    }
    return 0;   //Done converting unit to PU
}

Bus::~Bus()
{
    //dtor
}
