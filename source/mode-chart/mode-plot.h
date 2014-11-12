#ifndef MODEPLOT_H
#define MODEPLOT_H



#include "../plot/contourplot.h"
#include "../vector/equations.h"
#include "../mode-chart/mode_computer.h"

template<size_t state_size, size_t param_size>
struct ContourPlotMode : public ContourPlot<state_size, param_size>
{
    typedef state<state_size> state_s;
    typedef params<param_size> param_s;

    double computeTime_;
    int sequenceLength_;

    ContourPlotMode(state_s initS,
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
        ModeComputer<state_size, param_size> mode_computer(s, p, transitionTime_, sequenceLength_);

        std::vector<state_s> states = mode_computer.get_state_sequence(ds);
        int period = mode_computer.getPeriod(states, ds.isNear);
        f << period;
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
#endif // MODEPLOT_H
