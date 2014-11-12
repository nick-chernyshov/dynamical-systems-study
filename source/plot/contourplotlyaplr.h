//---------------------------------------------------------------------------

#ifndef contourplotlyapH
#define contourplotlyapH
//---------------------------------------------------------------------------
#include "equations.h"
#include "lyapunov.h"
#include "continuationplotlr.h"


struct ContourPlotLyap : public ContinuationPlotLR
{
	double ortogonalizationPeriod;
	int lyapVectorCount;

    double defaultLimit;
    state storeLyaps;

    ContourPlotLyap(state initS1Value, params pmin1Value, params pmax1Value, complex<int> axes1Value, complex<int> spans1Value, double trTiValue, double coTiValue, int seqLen1Value, int lvCount):
        ContinuationPlotLR(initS1Value, pmin1Value, pmax1Value, axes1Value, spans1Value, trTiValue, coTiValue, seqLen1Value)
	{
		ortogonalizationPeriod = coTiValue / seqLen1Value;
		lyapVectorCount = lvCount;
        defaultLimit = 1e-3;
        storeLyaps = 0.0;
	}
    void computePoint(params p, Equations & ode, ofstream & f) override;
    bool continuedFromLast() override;
};


#endif
