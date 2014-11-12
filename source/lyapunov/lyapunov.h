// ---------------------------------------------------------------------------

#ifndef lyapunovH
#define lyapunovH
// ---------------------------------------------------------------------------
#include "../vector/equations.h"
#include <vector>

enum LyapunovExpConstants
{
	pertValue = 1
};

template<size_t S_size, size_t param_size>
state<S_size> getLyapsPert(state<S_size> & s, params<param_size> & p, Equations<S_size, param_size> & ode, int N, double T,	int lvCount)
{
    state<S_size> sum(10.0);
    state<S_size> topSum(0.0);

    double bottomSum = 0.0;

    double ortPeriod = T;
    double h = ode.step;

    if (ode.isFixedPoint(s, p))
    {
        sum = -3.0;
        return sum;
    }

    vector<state<S_size> > lyaps = initializePertVectors<S_size>(lvCount);
    // tmp var for optimization

    for (int k = 0; k < 50; k++) // transition process
    {
        s = integrateLyaps(s, lyaps, p, ode, ortPeriod);
        ortgsPert(sum, lyaps);
        if (ode.isOut(s)) {
            sum = 3.0;
            return  sum;
        }
    }

    sum.fill(double(0.0));

    double totalTime = 0;
    ode.step = h * ortPeriod / ceil(ortPeriod);
    for (int k = 1; k <= N; k++)
    {
        s = integrateLyaps(s, lyaps, p, ode, ortPeriod);
        totalTime += ortPeriod;

        if (ode.isOut(s))
            break;
        else
        {
            ortgsPert(sum, lyaps);
            topSum = topSum + totalTime * sum;
            bottomSum += totalTime * totalTime; // this code for the least squre approx
        }
    }
    if (!ode.isOut(s))
    {
        sum = sum / totalTime;// the least squre approx v.:
        //sum = topSum/bottomSum;
    }
    else
    {
        sum = 3.0;
    }
    ode.step = h;

    return sum;

}

template<size_t S_size>
std::vector<state <S_size> >initializePertVectors(int lvCount)
{
    std::vector<state<S_size> > lyaps;


    for (int i = 0; i < lvCount; i++)
    {
        state<S_size> tmp;
        lyaps.push_back(tmp);
        lyaps[i] = 0.0;
        lyaps[i][i] += pertValue;
    }

    return lyaps;
}

template<size_t S_size>
void destroyPertVectors(state<S_size> * s)
{
    delete [] s;
}

template<size_t S_size, size_t param_size>
state<S_size> integrateLyaps(state<S_size> ns, vector<state<S_size> > & lv, params<param_size> & p,
                                 Equations<S_size, param_size> & ode, double time)
{
    std::vector<std::vector<state<S_size> > > tmpArr(4);
    for (int i = 0; i < tmpArr.size(); i++)
    {
        tmpArr[i].resize(lv.size());
    }

    for (double t = 0; t < time; t += ode.step)
    {
        makeOdeStepLyap(ns, lv, p, ode, tmpArr);
    }

    return ns;

}

template<size_t S_size, size_t param_size>
void makeOdeStepLyap(state<S_size> & ns, vector<state<S_size> > & lv, params<param_size> & p,
                     Equations<S_size, param_size> & ode, std::vector<std::vector<state<S_size> > > & butcherTable)
{
    double h = ode.step;

    state<S_size> s = ns;
    state<S_size> l;

    for (int i = 0; i < lv.size(); i++) {
        l = lv[i];
        butcherTable[0][i] = ode.pertEq(s, l, p);
        butcherTable[0][i] *= h;
    }
    state<S_size> k1 = ode.dst(s, p);
    k1 *= h;
    s = (k1 * 0.5);
    s += ns;

    for (int i = 0; i < lv.size(); i++) {
        l  = butcherTable[0][i];
        l *= 0.5;
        l += lv[i];
        butcherTable[1][i]  = ode.pertEq(s, l, p);
        butcherTable[1][i] *= h;
    }
    state<S_size> k2 = ode.dst(s, p);
    k2 *= h;
    s = (k2 * 0.5);
    s += ns;

    for (int i = 0; i < lv.size(); i++) {
        l  = butcherTable[1][i];
        l *= 0.5;
        l += lv[i];
        butcherTable[2][i]  = ode.pertEq(s, l, p);
        butcherTable[2][i] *= h;
    }
    state<S_size> k3 = ode.dst(s, p);
    k3 *= h;
    s = k3 + ns;
    for (int i = 0; i < lv.size(); i++) {
        l = lv[i];
        l += butcherTable[2][i];
        butcherTable[3][i]  = ode.pertEq(s, l, p);
        butcherTable[3][i] *= h;
    }
    state<S_size> k4 = ode.dst(s, p);
    k4 *= h;
    for (int i = 0; i < lv.size(); i++) {
        lv[i] = lv[i] + sixth * (2 * (butcherTable[1][i] + butcherTable[2][i]) + butcherTable[0][i] + butcherTable[3][i]);
    }
    ns = ns + sixth * (k1 + k4 + 2.0 * (k2 + k3));
}

template<size_t S_size>
void ortgsPert(state<S_size> & sum, vector<state<S_size> > & a)
{
    size_t n = a.size();

    state<S_size> res;
    res = 0;

    for (int i = 0; i < n; i++)	{
        for (int j = 0; j < i; j++)	{
            state<S_size> proj = (a[i] * a[j]) * a[j];
            a[i] = a[i] - proj;
        }
        double diss = LinAlg<S_size>::norm(a[i]) / pertValue;
        if (diss > 1e-8) {
            res[i] += log(diss);
            a[i] = LinAlg<S_size>::ort(a[i]);
        }
        else {
            res[i] -= 16;
            a[i] = 0;
            a[i][i] = 1;
        }
        sum[i] += res[i];
    }
    for (int i = 0; i < n; i++)
    {
        a[i] = pertValue * a[i];
    }
}

#endif
