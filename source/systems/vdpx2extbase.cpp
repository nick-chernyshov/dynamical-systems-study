//---------------------------------------------------------------------------

#include "vdpx2extbase.h"

//---------------------------------------------------------------------------
using namespace Vdp2ExtBaseDS;
using namespace std;

state<state_size> Vdp2ExtBase::dst(state<state_size> & s, params<param_size> & p) {


    state<state_size> r = s;
    double & d1 = p[0];
    double & d2 = p[1];
    double & ep = p[2];
    double & f = p[3];
    double & a = p[4];
    double & lmbd = p[5];

    double & x1 = s[0];
    double & x2 = s[1];
    double & x3 = s[2];
    double & x4 = s[3];
    double & t = s[4];

    double acft =  a * cos(f*t);

    r[0] = x2;
    r[1] = (lmbd - x1*x1)*x2 - (1+d1) * x1 - ep * (x1 - x3) + acft;
    r[2] = x4;
    r[3] = (lmbd - x3*x3)*x4 - (1+d2) * x3 - ep * (x3 - x1);
    r[4] = 1;
    return r;
}


state_s Vdp2ExtBase::pertEq(state<state_size> & s, state<state_size> & sp, params<param_size> & p) {

    state<state_size> r; r = 0;
    double & d1 = p[0];
    double & d2 = p[1];
    double & ep = p[2];
    double & f = p[3];
    double & a = p[4];
    double & lmbd = p[5];

    double & dx1 = sp[0];
    double & dx2 = sp[1];
    double & dx3 = sp[2];
    double & dx4 = sp[3];
    double & dx7 = sp[4];

    double & x1 = s[0];
    double & x2 = s[1];
    double & x3 = s[2];
    double & x4 = s[3];
    double & t = s[4];
    double afsft =  a * f * sin(f*t);

    r[0] = dx2;
    r[1] = dx1 * (-1-ep - 2*x1*x2 - d1) + dx2 * (lmbd - x1*x1) + dx3*ep + dx7 * afsft;
    r[2] = dx4;
    r[3] = dx3 * (-1-ep-2*x3*x4 - d2) + dx4 * (lmbd - x3*x3) + dx1*ep;
    r[4] = 0;

    return r;
}


