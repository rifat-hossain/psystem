#include <iostream>
#include "../../cpp_library/include/psystem.h"

using namespace std;

int main()
{
    psystem ps;
    ps.addBus(Bus(Bus::VD_BUS, 22e3,0,false));
    ps.addBus(Bus(Bus::PQ_BUS, 0,0,false));
    ps.addBus(Bus(Bus::PQ_BUS, 0,0,false));
    ps.addBus(Bus(Bus::PQ_BUS, 34.2e6,45.6e6,false));
    ps.addBus(Bus(Bus::PQ_BUS, 0,0,false));
    ps.addBus(Bus(Bus::PQ_BUS, 0,0,false));

    ps.addConn(Connection(1,0,0,0.18,90e6,22e3,1));
    ps.addConn(Connection(1,2,0,0.1,50e6,22e3,10));
    ps.addConn(Connection(2,3,0,48.4,1));
    ps.addConn(Connection(3,4,0,0.06,40e6,220e3,0.05));
    ps.addConn(Connection(1,5,0,0.064,40e6,22e3,5));
    ps.addConn(Connection(5,6,0,65.43,1));
    ps.addConn(Connection(6,4,0,0.08,40e6,110e3,0.1));
    ps.addConn(Connection(4,0,0,0.185,66.5e6,10.45e3,1));

    ps.make_pu(22e3,100e6,2);

    ps.init_ybus();
    complex<double> element;
    cout << "Ybus=" << endl;
    for(int i=1; i <= 4;i++){
        for(int j=1; j <= 4; j++){
            ps.get_ybus_element(element, i, j);
            cout << "\t\t" << element;
        }
        cout << endl;
    }
    return 0;
}
