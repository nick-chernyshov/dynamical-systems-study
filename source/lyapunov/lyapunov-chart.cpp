//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../systems/vdpx2extbase.h"
#include "../lyapunov/contourplotlyap.h"



//---------------------------------------------------------------------------
using namespace std;

template<size_t state_s, size_t param_s>
string readContourPlotTask(string ifName, ContourPlot<state_s, param_s> & plot) {

    fstream inpConf(ifName.c_str(), ifstream::in);
    string rs("");
    string tmpStr("");


    stringstream s2vStream(stringstream::in | stringstream::out);
    int px = -1, py = -1;
    for (int i = 0; i < (int)param_s || py == -1; i++) {
        inpConf >> tmpStr;
        if (tmpStr != string(":")) {
            inpConf >> plot.pmin_[i];
            s2vStream << tmpStr << string("=");
            s2vStream << plot.pmin_[i] << string(" ");
        }
        else {
            i-- ;
            if (px == -1) {
                px = i;
            }
            else {
                py = i;
            }
            inpConf >> plot.pmax_[i];
            s2vStream << string(" - ") << plot.pmax_[i] << string(" ");
        }
    }

    for (int i = 0; i < (int)state_s; i++) {
        inpConf >> tmpStr >> plot.s_[i];
        s2vStream << tmpStr << string("=") << plot.s_[i] << " ";
    }

    size_t width = 0, height = 0;

    inpConf >> tmpStr >> width >> tmpStr >> height;
    s2vStream << string("w= ") << width << string(" h= ") << height << string(" ");


    rs = s2vStream.str()+".txt";

    inpConf.close();

    plot.spans_.width = width;
    plot.spans_.height = height;
    plot.axes_.x = px;
    plot.axes_.y = py;

    return rs;
}

int main()
{
    using namespace Vdp2ExtBaseDS;

    Vdp2ExtBase ds(0.005, 1000.0, 0.00001);

    params_s pmin(0.0);
    params_s pmax(0.0);
    state_s inPh(0.0);


    Axes axes = {0,1};
    Spans spans = {0,0};


    double transTime = 500.0, computeTime = 500.0;
    int seqLen = 100, lyapCount = 2;

    ContourPlotLyap<state_size, param_size>
            lyapMap(inPh, pmin, pmax, axes, spans, transTime, computeTime, seqLen, lyapCount);

    string ftask("task.txt");
    string fconfig("config.txt");
    lyapMap.readConfig(fconfig, ds);
    lyapMap.readTask(ftask);
    lyapMap.buildContourPlot(ds);

    return 0;
}
//---------------------------------------------------------------------------

