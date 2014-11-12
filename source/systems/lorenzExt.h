#ifndef LORENZ_H
#define LORENZ_H

#include "../vector/equations.h"

namespace LorenzExt
{
static const size_t state_size = 4;
static const size_t param_size = 5;

typedef state<state_size> state_s;
typedef params<param_size> params_s;

using namespace std;

class lorenzExt : public Equations<state_size, param_size> {
public:
    double T;

    lorenzExt(double initStep, double initInfValue, double isNearValue):
        Equations<state_size, param_size>(initStep, initInfValue, isNearValue) { T = 0; }

    state_s dst(state_s  & s, params_s & p) override;
    void init(state_s & s, params_s & p) override;

};
}
#endif // LORENZ_H
