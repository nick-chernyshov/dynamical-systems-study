#ifndef VPD3RINGBASEDS_H
#define VPD3RINGBASEDS_H

//---------------------------------------------------------------------------

#include "../vector/equations.h"

namespace Vdp3RingBaseDS {

static const size_t state_size = 6;
static const size_t param_size = 5;

typedef state<state_size> state_s;
typedef params<param_size> params_s;

struct Vdp3RingBase: public Equations<state_size, param_size>
{
    state_s dst(state_s & s, params_s  & p) override;
    state_s pertEq(state_s & s, state_s & sp, params_s & p) override;
    Vdp3RingBase(double initStep, double initInfValue, double isNearValue): Equations<state_size, param_size>(initStep, initInfValue, isNearValue){}
};
}
#endif // VPD3BASEDS_H
