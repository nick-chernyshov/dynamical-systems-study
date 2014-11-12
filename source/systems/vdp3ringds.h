#ifndef VDP3RINGDS_H
#define VDP3RINGDS_H

#include "../vector/equations.h"

namespace Vdp3RingPhaseDS
{

static const size_t state_size = 2;
static const size_t param_size = 4;

typedef state<state_size> state_s;
typedef params<param_size> params_s;

using namespace std;

struct Vdp3RingDS : public Equations<state_size, param_size> {
    state<state_size> dst(state<state_size> & s, params<param_size>  & p) override;
    Vdp3RingDS(double initStep, double initInfValue, double isNearValue): Equations<state_size, param_size>(initStep, initInfValue, isNearValue) {
    }
    state_s pertEq(state_s & s, state_s & sp, params_s  & p) override;



};

}

#endif // VDP3RINGDS_H
