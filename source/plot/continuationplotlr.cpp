#include "continuationplotlr.h"


void ContinuationPlotLR::buildContourPlot(Equations &ode, ofstream &out)
{
    int px = axes_.real(), py = axes_.imag(), width = spans_.real(), height = spans_.imag();
    double dx = (pmax_[px] - pmin_[px])/width, dy = (pmax_[py] - pmin_[py])/height;
    params p = pmin_;
    state st = s_;
    for (int j = 0; j <= height; j++) {
        s_ = st;
        for (int i = 0; i <= width; i++) {
            if (!continuedFromLast())
                s_ = st;
            p[px] = pmin_[px] + dx*i;
            p[py] = pmin_[py] + dy*j;
            out << p[axes_.real()] << " " << p[axes_.imag()] << " ";
            computePoint(p, ode, out);
            out << "\r\n";
        }
        out.flush();
        std::cout << "row " << j << endl;
    }
}



