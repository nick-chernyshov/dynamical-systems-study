//---------------------------------------------------------------------------

#include "vdp3phaseds.h"


//---------------------------------------------------------------------------

using namespace Vdp3PhaseDS;
using namespace std;

state<state_size> Vdp3Phase::dst(state<state_size> & s, params<param_size> & p) {

    state<state_size> r(s);
    double sinx = sin(s[0]);
    double siny = sin(s[1]);
    double cosx = cos(s[0]);
    double cosy = cos(s[1]);

    double & d1 = p[0];
    double & d2 = p[1];
    double & d3 = p[2];
    double & ep = p[3];

    double  ep2 = ep*ep;

    r[0] =(- ep - d2 + ep * cosy + ep2 * (siny*cosx - 0.5 * sinx*cosy+siny*cosy-2*sinx*cosx));
    r[1] =( ep + d2 - d3 - ep * cosx + ep2 * (sinx*cosy - 0.5 * siny*cosx+sinx*cosx-2*siny*cosy));

    return r;
}

