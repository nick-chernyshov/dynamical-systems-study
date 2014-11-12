//---------------------------------------------------------------------------

#ifndef contourplotlyapH
#define contourplotlyapH
//---------------------------------------------------------------------------
#include "../plot/contourplot.h"
#include "../vector/equations.h"
#include "../lyapunov/lyapunov.h"

template <size_t state_size, size_t param_size>
struct ContourPlotLyap : public ContourPlot<state_size, param_size>
{
    double ortPeriod_;
    int lyapVectorCount_;

    double defaultLimit_;
    state<state_size> storeLyaps_;

    double computeTime_;
    int sequenceLength_;
    state<state_size> init_state;

    ContourPlotLyap(state<state_size> s, params<param_size> pmin, params<param_size> pmax, Axes axes, Spans spans, double transitionTime, double computeTime, int sequenceLength, int lvCount):
        ContourPlot<state_size, param_size>(s, pmin, pmax, axes, spans, transitionTime), init_state(s)
	{
        computeTime = computeTime_; sequenceLength_ = sequenceLength;
        ortPeriod_ = computeTime_ / sequenceLength_;
        lyapVectorCount_ = lvCount;
        defaultLimit_ = 1e-3;
        storeLyaps_ = 0.0;
	}
    void computePoint(params<param_size> p, Equations<state_size, param_size> & ode, fstream & f) override
    {

        /* Only for nonautonomous system */
        if (storeLyaps_[0] >= 0)
            s_ = init_state;
        double & frequence = p[3]; // frequence of external force
        double & t = s_[state_size-1]; // time counter, dynamical variable
        double T = 2*M_PI / frequence; // period of external force
        while (t > 0) t -= T;
        /* Only for nonautonomous system */


        s_ = ode.integrate(s_, p, transitionTime_);

        storeLyaps_ = getLyapsPert(s_, p, ode, sequenceLength_, ortPeriod_, lyapVectorCount_);

        for (int i = 0; i < (int)storeLyaps_.size(); i++)
            f << storeLyaps_[i] << " " ;
    }
    void readPoint(fstream &f) override
    {
        if (!f.is_open())
            return;
        while (f.good())
        {
            double px, py, tmp;
            f >> px >> py;
            for (int i = 0; i < (int)storeLyaps_.size(); i++)
                f >> tmp;
            built_points_.insert(make_pair(px, py));
        }
    }

    void readConfig(string ifName, Equations<state_size, param_size> & DS) override {
        string tmpStr;
        fstream inpConf(ifName.c_str(), ifstream::in);
        inpConf >> tmpStr >>this->transitionTime_ >> tmpStr >> this->computeTime_ >>
                   tmpStr >> this->sequenceLength_ >> tmpStr >> this->lyapVectorCount_;
        inpConf >> tmpStr >>DS.step >> tmpStr >> DS.infValue >> tmpStr >> DS.isNear;

        this->ortPeriod_ = this->computeTime_ / this->sequenceLength_;

        inpConf.close();
    }

    void readTask(string ifName) override
    {
        ContourPlot::readTask(ifName);
        init_state = s_;
    }


};


#endif
