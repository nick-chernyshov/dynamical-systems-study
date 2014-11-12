#include "lorenzExt.h"

//---------------------------------------------------------------------------
using namespace LorenzExt;

state_s lorenzExt::dst(state_s &s, params_s &p)
{



    state_s rVal = s;
    double & sigma = p[0];
    double & r = p[1];
    double & b = p[2];
    double & f = p[3];
    double & a = p[4];

    double & x = s[0];
    double & y = s[1];
    double & z = s[2];
    double & t = s[3];

    rVal[0] = sigma*(y-x);
    rVal[1] = x * (r-z)-y;
    rVal[2] = x*y - b*z + a * cos(f*t);;
    rVal[3] = 1;

    return rVal;

}

void lorenzExt::init(state_s&  s, param_s & p)
{
    if (T == 0)
    {
        T = 2 * M_PI/p[3];
        step = T / ceil(T) * step;
    }
    else
    {
        s[3] = fmod(s[3], T);
    }
}
