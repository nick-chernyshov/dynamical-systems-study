//---------------------------------------------------------------------------

#ifndef windingnumbersH
#define windingnumbersH
//---------------------------------------------------------------------------
#include "../vector/equations.h"
#include <utility>
//---------------------------------------------------------------------------

template<size_t state_size>
struct Section
{
    int side_;
    state<state_size> s_;
};

template<size_t state_size, size_t parameter_size>
struct WindingNumbers {
    typedef state<state_size> state_s;
    typedef params<parameter_size> param_s;

    WindingNumbers(size_t  sectionArrayLength = 250,
                   double maxTime = 100.0,
                   double nearValue = 0.001) :
                   sectionArrayLength_(sectionArrayLength),
                   maxTime_(maxTime),
                   nearValue_(nearValue)
    {}

    size_t sectionArrayLength_;
    double maxTime_;
    double nearValue_;

    state_s getNextSection(state_s & s,
                           param_s & p,
                           Equations<state_size, parameter_size> & ode)
    {
        bool crossed  = false, stepWasReduced = false;
        state_s st = s;
        double h = ode.step;
        state_s rVal(0.0);

        for (double t = 0; t < maxTime_; t+=ode.step)
        {
            st = s;
            s = ode.ode45(s, p);
            if (!crossed)
            for (int i = 0; i < state_size; i++)
            {
                if (abs(s[i]) > M_PI && abs(st[i]) < M_PI)
                {

                    if (stepWasReduced)
                    {
                        ode.step = ode.step * (abs(s[i]) - M_PI)/(abs(s[i])-abs(st[i]));
                        crossed = true;
                    }
                    else
                    {
                        ode.step = h * 0.01;
                        stepWasReduced = true;
                    }
                    s = st;
                }
            }
            else
            {
                rVal = s;
                ode.step = h;
                s = ode.ode45(s, p);
                s %= 2*M_PI;
                return rVal;
            }
        }
        return rVal;
    }

    vector<state_s> getSectionArray(state_s & s,
                                    param_s & p,
                                    Equations<state_size, parameter_size> & ode)
    {
        vector<state_s> rVal;
        state_s s1 = s, s2;
        for (int i = 0; i < sectionArrayLength_; i++)
        {
            s2 = s1;
            s1 = getNextSection(s, p, ode);

            s2-=s;
            vector<int> windingNumbers = getWindingNumber(s1);
            if (windingNumbers.empty())
                if (LinAlg<state_size>::norm(s2) < nearValue_)
                {
                    return rVal;
                }
                else
                {                          
                    rVal.push_back(s1);
                    return rVal;
                }
            rVal.push_back(s1);
        }
        return rVal;
    }

    vector<int> getWindingNumber(state_s & s)
    {      
        vector<int> rVal;
        for (int i = 0; i < s.size(); i++)
        {
            if (abs(s[i]-M_PI) < nearValue_)
                rVal.push_back(i+1);
            else if (abs(s[i]+M_PI) < nearValue_)
                rVal.push_back(-(i+1));
        }

        if (!rVal.empty())
            return rVal;

        bool isFixedPoint = true;
        for(int i = 0; i < s.size(); i++)
        {
            double val = s[i];
            if (val != 0.0) isFixedPoint = false;
        }

        if (isFixedPoint)
            return rVal;
        else {
            rVal.push_back(0.0);
        }

        return rVal;


    }

    vector<int> getWindingNumbers(vector<state_s> & sections)
    {
        vector<int> rVal;

        if (sections.empty())
            return rVal;

        for (int i = 0; i < sections.size(); i++)
        {
            vector<int> sectionWNSet = getWindingNumber(sections[i]);        
            if (sectionWNSet.empty())
            {
                rVal.push_back(0);
            }
            else for (int j = 0; j < sectionWNSet.size(); j++)
            {
                rVal.push_back(sectionWNSet[j]);
            }
        }
        return rVal;
    }

    vector<int> getPeriodFromSequence(vector<int> & sequence)
    {
        vector<int> rVal(state_size, 0);
        if (sequence.size() && sequence[0] == 0)
        {
            rVal.push_back(1);
            return rVal;
        }

        for (int i = 1; i <= sequence.size()/2; i++)
        {
            if (i == sequence.size()/2)
            {
                for (int j = 0; j < rVal.size(); j++)
                {
                    rVal[j] = 10000;
                }
                rVal.push_back(-1);
                return rVal;
            }

            bool periodFound = true;
            for (int j = 0; j < sequence.size()-i; j++)
            {
                if (sequence[j] != sequence[i+j])
                {
                    periodFound = false;
                    break;
                }
            }
            if (periodFound)
            {
                for (int j = 0; j < i; j++)
                {
                    if (sequence[j] > 0)
                        rVal[abs(sequence[j])-1] ++;
                    else
                        rVal[abs(sequence[j])-1] --;
                }
                rVal.push_back(1);
                return rVal;
            }
        }
        rVal.push_back(0);
        return rVal;
    }
};

#endif
