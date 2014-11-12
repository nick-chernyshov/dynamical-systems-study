//---------------------------------------------------------------------------

#ifndef vdp3ExtDSH
#define vdp3ExtDSH
//---------------------------------------------------------------------------
#include "../vector/equations.h"

namespace Vdp3ExtDS
{

static const size_t state_size = 3;
static const size_t param_size = 6;

typedef state<state_size> state_s;
typedef params<param_size> params_s;

using namespace std;

struct Vdp3Ext: public Equations<state_size, param_size> {

    Vdp3Ext(double initStep, double initInfValue, double isNearValue):
        Equations<state_size, param_size>(initStep, initInfValue, isNearValue) { }

    state_s dst(state_s & s, params_s  & p) override;
    state_s pertEq(state_s & s, state_s & sp, params_s  & p) override;


};
}


#endif
