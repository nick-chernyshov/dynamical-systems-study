//---------------------------------------------------------------------------
#include "contourplotlyap.h"


void ContourPlotLyap::computePoint(params p, Equations & ode, ofstream & f)
{
//    ode.init(s_, p);
    s_ = ode.integrate(s_, p, transitionTime_);

    storeLyaps = getLyapsPert(s_, p, ode, sequenceLength_, ortogonalizationPeriod, lyapVectorCount);

    for (int i = 0; i < (int)storeLyaps.size(); i++)
        f << storeLyaps[i] << " " ;
}
//---------------------------------------------------------------------------
bool ContourPlotLyap::continuedFromLast()
{
    if (storeLyaps[0] < defaultLimit && storeLyaps[1] < -defaultLimit)
        return true;

    return false;
}
