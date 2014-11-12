//---------------------------------------------------------------------------

#ifndef vdpx2extbaseH
#define vdpx2extbaseH
//---------------------------------------------------------------------------
#include "../vector/equations.h"
namespace Vdp2ExtBaseDS
{
static const size_t state_size = 5;
static const size_t param_size = 6;

typedef state<state_size> state_s;
typedef params<param_size> params_s;

using namespace std;

struct Vdp2ExtBase: public Equations<state_size, param_size> {


    state<state_size> dst(state<state_size> & s, params<param_size>  & p) override;
    Vdp2ExtBase(double initStep, double initInfValue, double isNearValue)
        : Equations<state_size, param_size>(initStep, initInfValue, isNearValue) {
    }
    state_s pertEq(state_s & s, state_s & sp, params_s & p)
    override;
};
}
#endif
