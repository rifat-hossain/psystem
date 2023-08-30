#ifndef PSYSTEM_H
#define PSYSTEM_H
#include "Bus.h"
#include "Connection.h"
#include <math.h>
#include <vector>

class psystem
{
    public:
        psystem();
        int addBus(Bus bus);
        int getBus(Bus& bus, int index);
        int addConn(Connection conn);
        int getConn(Connection& conn, int index);
        int init_ybus();
        int get_ybus_element(complex<double>& element, int i, int j);
        int make_pu(double v_base, double s_base, int bus_id);
        int analyze_powerflow(int iteration);
        virtual ~psystem();

    protected:

    private:
        vector<Bus> buses;
        vector<Connection> conns;
        vector<complex<double>> ybus;
        int pu_helper(double v_base, double s_base, int bus_id);
        int current_element(complex<double>& I, int bus_id);
};

#endif // PSYSTEM_H

