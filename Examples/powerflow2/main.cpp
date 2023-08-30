#include <iostream>
#include "../../cpp_library/include/psystem.h"

using namespace std;

int main()
{
    psystem ps;
    ps.addBus(Bus(Bus::VD_BUS,1.05,0,true));
    ps.addBus(Bus(Bus::PQ_BUS,-2.566,-1.102,true));
    ps.addBus(Bus(Bus::PQ_BUS,-1.386,-0.452,true));

    ps.addConn(Connection(1,2,0.02,0.04,1));
    ps.addConn(Connection(1,3,0.01,0.03,1));
    ps.addConn(Connection(2,3,0.0125,0.025,1));

    ps.init_ybus();
    ps.analyze_powerflow(7);
    Bus b;
    ps.getBus(b,2);
    cout << polar(b.v,b.d) << endl;
    return 0;
}
