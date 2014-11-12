#ifndef CONTINUATIONPLOTLR_H
#define CONTINUATIONPLOTLR_H

#include "contourplot.h"

class ContinuationPlotLR : public ContourPlot
{
public:
    ContinuationPlotLR(state initS, params pmin, params pmax, complex<int> axes, complex<int> spans, double transitionTime, double computanceTime, int sequenceLength) :
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

#endif // CONTINUATIONPLOTLR_H
