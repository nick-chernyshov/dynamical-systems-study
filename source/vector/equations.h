// ---------------------------------------------------------------------------

#ifndef equationsH
#define equationsH
// ---------------------------------------------------------------------------
#include "../vector/linearalgebra.h"

#include <vector>
#include <algorithm>
#include <numeric>
#include <valarray>
#include <utility>

using namespace std;


template<size_t S_size, size_t P_size>
struct Equations {

    typedef state<S_size> state_eq;
    typedef params<P_size> param_s;

    double step, infValue, isNear, T_;

public:

        enum integrationConstants
        {
            fixedPointIters = 200
        };

        Equations(double initStep, double initInfValue, double isNearValue) {
            step = initStep;
            infValue = initInfValue;
            isNear = isNearValue;
        }

        virtual int isOut(state_eq s) {
            double sum = 0;
            for (unsigned i = 0; i < s.size(); i++) {
                sum += s[i]*s[i];
            }
            return sum > infValue*infValue;
        }

        virtual void init(state_eq & s, params<P_size> & p)
        {
        }

        virtual state_eq dst(state_eq & s, params<P_size> & p) = 0;

        state_eq ode45(state_eq & ns, params<P_size>  & p)
        {
            if (isOut(ns))
                return ns;

            state_eq s(ns);

            state_eq k1=dst(s,p); k1 *= step;
            s = k1;	s *= 0.5; s += ns;

            state_eq k2=dst(s,p); k2 *= step;
            s = k2;	s *= 0.5; s += ns;

            state_eq k3=dst(s,p); k3 *= step;
            s = k3; s += ns;

            state_eq k4 = dst(s,p); k4 *= step;

            k2 += k3;
            k2 *= 2;

            s = k1;
            s += k4;
            s += k2;

            s *= sixth;
            s += ns;

            return s;

        }



        state_eq integrate(state_eq s, params<P_size>  & p,  double time)
        {
            double maxDeltaT = abs(step) / 2;
            for (double t=0; abs(t-time)>  maxDeltaT ; t+=abs(step)){
                init(s, p);
                if (isOut(s)) {
                    break;
                }
                else {
                    s = ode45(s, p);
                }
            }
            return s;
        }

        int isFixedPoint(state_eq  & s  , params<P_size>  & p)
        {
            state_eq s1 = integrate(s, p, 1.0);
            s1 = dst(s1, p);
            if (LinAlg<S_size>::norm(s1)*abs(step) < 1e-8) {
                return 1;
            }
            else {
                return 0;
            }
        }
        virtual ~Equations(){}
        virtual state_eq pertEq(state_eq & s, state_eq & sp, param_s & p)
        {
            return sp;
        }
    };



#endif
