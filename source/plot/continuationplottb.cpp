#include "continuationplottb.h"

void ContinuationPlotTB::buildContourPlot(Equations &ode, ofstream &out)
{
    int px = axes_.real(), py = axes_.imag(), width = spans_.real(), height = spans_.imag();
    double dx = (pmax_[px] - pmin_[px])/width, dy = (pmax_[py] - pmin_[py])/height;
    params p = pmin_;
    state st = s_;
    for (int i = width; i >= 0; i--) {
        s_ = st;
        for (int j = height; j >= 0; j--) {
            if (!continuedFromLast())
                s_ = st;
            p[px] = pmin_[px] + dx*i;
            p[py] = pmin_[py] + dy*j;
            out << p[axes_.real()] << " " << p[axes_.imag()] << " ";
            computePoint(p, ode, out);
            out << "\r\n";
        }
        out.flush();
        std::cout << "col " << i << endl;
    }
}



