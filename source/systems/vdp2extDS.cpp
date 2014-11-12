//---------------------------------------------------------------------------
#include "vdp2ExtDS.h"


//---------------------------------------------------------------------------

state Vdp2ExtDS::dst(state & s, params & p) {

	unsigned const dimensions = 2; 	if (dimensions != s.size()) {out = 1; return s;}
	unsigned const parameterCount = 5; if (parameterCount != p.size()) {out = 1; return s;}

//	s = LinAlg::modx(s, 2*M_PI);

	state r = s;
	if (out)
	{
		r = 0;
	}
	else
	{
		double s12 = sin(s[0]-s[1]);
		double c12 = cos(s[0]-s[1]);

		double & d1 = p[0];
		double & d2 = p[1];
		double & ep = p[2];
		double & f = p[3];
		double & a = p[4];

		double  ep2 = ep*ep;

		double & x1 = s[0];
		double & x2 = s[1];

        r[0] = d1 - 0.5*a*cos(x1) + ep*(1-c12) - ep2*(c12*s12) - 2*f;
        r[1] = d2 + ep*(1-c12) + ep2*(c12*s12) - 2*f;
	}
	return r;
}
