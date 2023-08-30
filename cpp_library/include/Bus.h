#ifndef BUS_H
#define BUS_H
#include <iostream>
#include <complex>

using namespace std;

class Bus
{
    public:
        Bus();
        double v;
        double d;
        double p;
        double q;
        Bus(int type, double val1, double val2, bool ispu);
        enum bType{
            VD_BUS,
            PQ_BUS,
            PV_BUS
        } BusType;
        double v_base;
        double s_base;
        uint8_t type;
        int make_pu(double s_base, double v_base);
        virtual ~Bus();

    protected:

    private:
        bool ispu = false;
        complex<float> vcom;
};

#endif // BUS_H
