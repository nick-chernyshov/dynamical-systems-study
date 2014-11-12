#ifndef TORUSCHART_H
#define TORUSCHART_H

#include "../plot/contourplot.h"
#include "../vector/equations.h"
#include "../torus/windingnumbers.h"

template<size_t state_size, size_t param_size>
struct ContourPlotTorus : public ContourPlot<state_size, param_size>
{
    typedef state<state_size> state_s;
    typedef params<param_size> param_s;

    double computeTime_;
    int sequenceLength_;

    ContourPlotTorus(state_s initS,
                     param_s pmin,
                     param_s pmax,
                     Axes axes,
                     Spans spans,
                     double transitionTime,
                     double computeTime,
                     int sequenceLength) :
        ContourPlot<state_size, param_size>(initS, pmin, pmax, axes, spans, transitionTime),
        computeTime_(computeTime),
        sequenceLength_(sequenceLength)
    {

    }
    void computePoint(params<param_size> p, Equations<state_size, param_size> & ds, fstream & f)
    {
        state_s s = s_;

        s = ds.integrate(s, p, transitionTime_);
        s %= 2*M_PI;
        WindingNumbers<state_size, param_size> wn(sequenceLength_, computeTime_);
        vector<int> sections = wn.getWindingNumbers(wn.getSectionArray(s, p, ds));
        vector<int> widingNumberValues = wn.getPeriodFromSequence(sections);

        for (int i = 0; i < widingNumberValues.size(); i++)        
            f << widingNumberValues[i] << " ";
    }

    void readConfig(string ifName, Equations<state_size, param_size> & DS) override
    {
        string tmpStr;
        fstream inpConf(ifName.c_str(), ifstream::in);

        inpConf >> tmpStr >>transitionTime_ >> tmpStr >> computeTime_ >>
                   tmpStr >> sequenceLength_;

        inpConf >> tmpStr >>DS.step >> tmpStr >> DS.infValue >> tmpStr >> DS.isNear;

        inpConf.close();
     }
};

#endif // TORUSCHART_H
