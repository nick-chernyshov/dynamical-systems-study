//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../systems/vdp3ExtDS.h"
#include "../torus/windingnumbers.h"
#include "../torus/toruschart.h"



//---------------------------------------------------------------------------
using namespace std;


int main()
{
    using namespace Vdp3ExtDS;

    Vdp3Ext ds(0.005, 1000.0, 0.00001);

    params_s pmin(0.0);
    params_s pmax(0.0);

    state_s inPh(0.0);

    Axes axes = {0,1};
    Spans spans = {0,0};


    double transTime = 500.0, computeTime = 500.0;
    int seqLen = 100;

    ContourPlotTorus<state_size, param_size>
            chart(inPh, pmin, pmax, axes, spans, transTime, computeTime, seqLen);

    string ftask("task.txt");
    chart.readTask(ftask);
    string fconfig("config.txt");
    chart.readConfig(fconfig, ds);
    chart.buildContourPlot(ds);
    return 0;
}
//---------------------------------------------------------------------------

