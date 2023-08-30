#ifndef CONNECTION_H
#define CONNECTION_H
#include <complex>

using namespace std;

class Connection
{
public:
    int terminal1;
    int terminal2;
    complex<double> Z;
    double K;
    double V;
    double S;
    double I;
    bool donepu;
    bool ispu;
    Connection();
    Connection(int terminal1, int terminal2, double R, double X, double k);
    Connection(int terminal1, int terminal2, double R_pu, double X_pu, double s, double v, double k);
    int make_pu(double v, double s);
    virtual ~Connection();

protected:

private:
};

#endif // CONNECTION_H
