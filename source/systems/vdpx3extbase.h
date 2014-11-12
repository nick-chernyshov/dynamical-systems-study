//---------------------------------------------------------------------------

#ifndef vdpx3extbaseH
#define vdpx3extbaseH
//---------------------------------------------------------------------------
#include "../vector/equations.h"

namespace Vdp3ExtBaseDS
{
static const size_t state_size = 7;
static const size_t param_size = 7;

typedef state<state_size> state_s;
typedef params<param_size> params_s;

using namespace std;

struct Vdp3ExtBase: public Equations<state_size, param_size> {


        Vdp3ExtBase(double initStep, double initInfValue, double isNearValue):         
            Equations<state_size, param_size>(initStep, initInfValue, isNearValue) {}

        state<state_size> dst(state<state_size> & s, params<param_size>  & p) override;

        state<state_size> pertEq(
                state<state_size> &s, state<state_size> &sp, params<param_size> &p) override;
};

}
#endif
