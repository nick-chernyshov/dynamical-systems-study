#ifndef MODE_COMPUTER_H
#define MODE_COMPUTER_H

#include "../vector/equations.h"
#include "../systems/lorenzExt.h"

template<size_t s_size, size_t p_size>

class ModeComputer
{
    state<s_size> s_;
    params<p_size> p_;
    double trans_;
    int maxPeriod_;
    double h;

public:
    ModeComputer(state<s_size> s, params<p_size> p, size_t trans, int maxPeriod) : s_(s), p_(p), trans_(trans), maxPeriod_(maxPeriod) {}

    typedef state<s_size> state_s;

    vector<state_s > get_state_sequence(Equations<s_size, p_size> & ode)
    {
        h = ode.step;


        s_ = ode.integrate(s_, p_, trans_);


        if (ode.isOut(s_))
            return vector<state<s_size> >();

        vector<state<s_size> > states;

        for (int i = 0; i < maxPeriod_; i++)
        {
            s_ = ode.integrate(s_, p_, ode.T_);
            states.push_back(s_);
        }

        return states;
    }

    int getPeriod(vector<state_s> & sequence, double nearValue)
    {
        if (sequence.empty())
            return -1;
        for (int i = 1; i <= sequence.size()/2; i++)
        {
            bool periodFound = true;
            for (int j = 0; j < sequence.size()-i; j++)
            {
                state_s s_tmp = sequence[j]-sequence[i+j];
                if (LinAlg<s_size>::norm(s_tmp) > nearValue)
                {
                    periodFound = false;
                    break;
                }
            }
            if (periodFound)
            {
                return i;
            }
        }
        return 10000;
    }


};

#endif // MODE_COMPUTER_H
