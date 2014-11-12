//---------------------------------------------------------------------------
#ifndef linearalgebraH
#define linearalgebraH
//---------------------------------------------------------------------------
#include <cmath>
#include <algorithm>
#include <valarray>
#include <numeric>
#include <vector>
#include "state.h"
#include "params.h"

using namespace std;

/*typedef valarray<double> state;
typedef valarray<double> params;*/


template <size_t S_size>
struct LinAlg {
    static double norm(state<S_size>  & x)
    {
        return sqrt(sqrNorm(x));
    }

    static state<S_size> ort(state<S_size> & x)
    {
        state<S_size> r = x;
        double len = norm(r);
        r /= len;
        return r;
    }

    static double distance(state<S_size> & x, state<S_size>  & y);
    static double sqrDistance(state<S_size> & x, state<S_size> & y)
    {
        if (x.size() != y.size()) {
            return 0;
        }
        else {
            double sum = 0;
            for (unsigned i = 0; i < x.size(); i++) sum += (x[i]-y[i])*(x[i]-y[i]);
            return sum;
        }
    }
    static double sqrNorm(state<S_size>  & x)
    {
        double sum = 0;
        for (unsigned i = 0; i < x.size(); i++)	sum += x[i]*x[i];
        return sum;
    }

    static int signum(double x) {return x > 0 ? 1 : -1;}
};

#endif
//------------------------------------------------------------------------------


