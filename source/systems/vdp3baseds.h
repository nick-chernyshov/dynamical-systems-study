#ifndef VPD3BASEDS_H
#define VPD3BASEDS_H

//---------------------------------------------------------------------------
#include "../vector/equations.h"
namespace Vdp3BaseDS
{
static const size_t state_size = 6;
static const size_t param_size = 5;

struct Vdp3Base:public Equations<state_size, param_size>
{
    state<state_size> dst(state<state_size> & s, params<param_size>  & p) override;

    Vdp3Base(double initStep, double initInfValue, double isNearValue): Equations<state_size, param_size>(initStep, initInfValue, isNearValue) {
    }
    state<state_size> pertEq(state<state_size> &s, state<state_size> &sp, params<param_size> &p) override;
};
}
#endif // VPD3BASEDS_H
