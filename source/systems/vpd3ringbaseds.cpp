#include "vpd3ringbaseds.h"

//---------------------------------------------------------------------------

using namespace Vdp3RingBaseDS;


state_s Vdp3RingBase::dst(state_s & s, params_s & p) {

    state_s r = s;
    double & d1 = p[0];
    double & d2 = p[1];
    double & d3 = p[2];
    double & ep = p[3];
    double & lmbd = p[4];

    double & x1 = s[0];
    double & x2 = s[1];
    double & x3 = s[2];
    double & x4 = s[3];
    double & x5 = s[4];
    double & x6 = s[5];

    r[0] = x2;
    r[1] = (lmbd - x1*x1)*x2 - (1+d1) * x1 - ep * (2*x1 - x3 - x5);
    r[2] = x4;
    r[3] = (lmbd - x3*x3)*x4 - (1+d2) * x3 - ep * (2*x3 - x1 - x5);
    r[4] = x6;
    r[5] = (lmbd - x5*x5)*x6 - (1+d3) * x5 - ep * (2*x5 - x3 - x1);

    return r;
}

state_s Vdp3RingBase::pertEq(state_s & s, state_s & sp, params_s & p) {

    state_s r; r = 0;

    double & d1 = p[0];
    double & d2 = p[1];
    double & d3 = p[2];
    double & ep = p[3];
    double & lmbd = p[4];

    double & dx1 = sp[0];
    double & dx2 = sp[1];
    double & dx3 = sp[2];
    double & dx4 = sp[3];
    double & dx5 = sp[4];
    double & dx6 = sp[5];

    double & x1 = s[0];
    double & x2 = s[1];
    double & x3 = s[2];
    double & x4 = s[3];
    double & x5 = s[4];
    double & x6 = s[5];

    r[0] = dx2;
    r[1] = dx1 * (-1 -2*ep -2*x1*x2 - d1) + dx2 * (lmbd - x1*x1) + dx3*ep + dx5*ep;
    r[2] = dx4;
    r[3] = dx3 * (-1 -2*ep -2*x3*x4 - d2) + dx4 * (lmbd - x3*x3) + dx5*ep + dx1*ep;
    r[4] = dx6;
    r[5] = dx5 * (-1 -2*ep -2*x5*x6 - d3) + dx6 * (lmbd - x5*x5) + dx3*ep + dx1*ep;

    return r;
}



