//---------------------------------------------------------------------------

#ifndef vdp3ExtDSH
#define vdp3ExtDSH
//---------------------------------------------------------------------------
#include "../vector/equations.h"

struct Vdp2ExtDS: public Equations {
    state dst(state & s, params  & p) override;
	Vdp2ExtDS(double initStep, double initInfValue, double isNearValue): Equations(initStep, initInfValue, isNearValue) {
		step = initStep;
		infValue = initInfValue;
		isNear = isNearValue;
		out = 0;
	}
};


#endif
