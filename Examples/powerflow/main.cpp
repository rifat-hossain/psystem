#include <iostream>
#include "../../cpp_library/include/psystem.h"

using namespace std;

int main()
{
    psystem ps;

    ps.addBus(Bus(Bus::VD_BUS,1.05,0,true));
    ps.addBus(Bus(Bus::PV_BUS,3,1,true));
    ps.addBus(Bus(Bus::PQ_BUS,4,2,true));

    ps.addConn(Connection(1,2,0,0.4,1));
    ps.addConn(Connection(1,3,0,0.3,1));
    ps.addConn(Connection(2,3,0,0.2,1));

    ps.init_ybus();
    ps.analyze_powerflow(1);

    Bus b;
    ps.getBus(b,2);
    cout << b.q << "<" << b.d << endl;
    return 0;
}
