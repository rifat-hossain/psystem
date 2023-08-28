#include "Connection.h"

Connection::Connection() {}
Connection::Connection(int terminal1, int terminal2, double R, double X, double k)
{
    this->V = -1;
    this->S = -1;
    this->donepu = false;
    this->terminal1 = terminal1;
    this->terminal2 = terminal2;
    this->Z = complex<double>(R,X);
    this->K = k;
    this->ispu = false;
}
Connection::Connection(int terminal1, int terminal2, double R_pu, double X_pu, double s, double v, double k)
{
    this->donepu = false;
    this->terminal1 = terminal1;
    this->terminal2 = terminal2;
    this->Z = complex<double>(R_pu,X_pu);
    this->K = k;
    this->V = v;
    this->S = s;
    this->ispu = true;
}
Connection::make_pu(double v, double s)
{
    donepu = true;
    if(!ispu)
    {
        Z = Z*s/pow(v,2);
        ispu = true;
    }
    else
    {
        Z = Z * pow(V/v,2) * s/S;
    }
    S = s;
    V = v;
}

Connection::~Connection()
{
    //dtor
}
