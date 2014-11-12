#include "vdp3ringds.h"

using namespace Vdp3RingPhaseDS ;
using namespace std;

state<state_size> Vdp3RingDS::dst(state<state_size> &s, params<param_size> &p)
{

    state<state_size> r = s;
    if (!isOut(s))
    {
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
    }
    else
    {
        r = 0;
    }
    return r;

}

