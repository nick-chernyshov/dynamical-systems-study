#ifndef CONTINUATIONPLOTTB_H
#define CONTINUATIONPLOTTB_H

#include "contourplot.h"

class ContinuationPlotTB : public ContourPlot
{
public:
    ContinuationPlotTB(state initS, params pmin, params pmax, complex<int> axes, complex<int> spans, double transitionTime, double computanceTime, int sequenceLength) :
        ContourPlot(initS, pmin, pmax, axes, spans, transitionTime, computanceTime, sequenceLength) {}

    void buildContourPlot(Equations & ode, ofstream & out) override;

    virtual bool continuedFromLast()
    {
        if (intDataVector.empty())
            return false;

        if (intDataVector.front() == (int)0)
            return true;

        return false;
    }

};

#endif // CONTINUATIONPLOTRL_H
