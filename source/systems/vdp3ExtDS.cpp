#include "vdp3ExtDS.h"

//---------------------------------------------------------------------------
using namespace Vdp3ExtDS;
using namespace std;

state_s Vdp3Ext::dst(state_s & s, params_s & p) {

    state_s r = s;
    if (isOut(s))
	{
		r = 0;
	}
	else
    {
        double & x1 = s[0];
        double & x2 = s[1];
        double & x3 = s[2];

        double s1 = sin(x1);
        double s2 = sin(x2);
        double s3 = sin(x3);
        double c1 = cos(x1);
        double c2 = cos(x2);
        double c3 = cos(x3);

        double c12 = c1*c2+s1*s2;
        double c23 = c2*c3+s2*s3;
        double s12 = s1*c2-s2*c1;
        double s23 = s2*c3-s3*c2;

		double & d1 = p[0];
		double & d2 = p[1];
		double & d3 = p[2];
		double & ep = p[3];
        double & W  = p[4];
        double & A  = p[5];

        double  ep2 = pow(ep,2);



        r[0] = -(A*c1)/2. + d1 + ep - c12*ep -
                (A*c12*ep*s1)/4. + (A*c12*ep*s2)/4. -
                2*W - c12*s12*pow(ep,2) +
                (c12*s23*pow(ep,2))/2.;
        r[1] = -(A*c2)/2. + d2 + 2*ep - c12*ep - c23*ep +
                (A*c12*ep*s1)/4. - (A*c12*ep*s2)/4. -
                (A*c23*ep*s2)/4. + (A*c23*ep*s3)/4. -
                2*W + c12*s12*pow(ep,2) +
                (c23*s12*pow(ep,2))/2. -
                (c12*s23*pow(ep,2))/2. - c23*s23*pow(ep,2);
        r[2] = -(A*c3)/2. + d3 + ep - c23*ep +
                (A*c23*ep*s2)/4. - (A*c23*ep*s3)/4. -
                2*W - (c23*s12*pow(ep,2))/2. +
                c23*s23*pow(ep,2);


    }
    return r;
}

state_s Vdp3Ext::pertEq(state_s &s, state_s &sp, params_s &p)
{
    state_s r(0.0) ;
    if (!isOut(s))
    {
        double & d1 = p[0];
        double & d2 = p[1];
        double & d3 = p[2];
        double & ep = p[3];
        double & W  = p[4];
        double & A  = p[5];

        double & x1 = s[0];
        double & x2 = s[1];
        double & x3 = s[2];

        double s1 = sin(x1);
        double s2 = sin(x2);
        double s3 = sin(x3);
        double c1 = cos(x1);
        double c2 = cos(x2);
        double c3 = cos(x3);

        double c12 = c1*c2+s1*s2;
        double c23 = c2*c3+s2*s3;
        double s12 = s1*c2-s2*c1;
        double s23 = s2*c3-s3*c2;

        double & dx1 = sp[0];
        double & dx2 = sp[1];
        double & dx3 = sp[2];


        r[0] = (A*(-(c1*c12*dx1*ep) + c12*c2*dx2*ep +
                   2*dx1*s1 + dx1*ep*s1*s12 -
                   dx2*ep*s1*s12 - dx1*ep*s12*s2 +
                   dx2*ep*s12*s2) +
                2*ep*(c12*c23*(dx2 - dx3)*ep +
                   (dx1 - dx2)*s12*
                    (2 + 2*ep*s12 - ep*s23) +
                   2*(-dx1 + dx2)*ep*c12*c12))/4.;
        r[1] =  (A*(c1*c12*dx1*ep - c12*c2*dx2*ep -
                    c2*c23*dx2*ep + c23*c3*dx3*ep -
                    dx1*ep*s1*s12 + dx2*ep*s1*s12 +
                    2*dx2*s2 + dx1*ep*s12*s2 -
                    dx2*ep*s12*s2 + dx2*ep*s2*s23 -
                    dx3*ep*s2*s23 - dx2*ep*s23*s3 +
                    dx3*ep*s23*s3) +
                 2*ep*(c12*c23*(dx1 - 2*dx2 + dx3)*ep +
                    2*dx1*s12 - 2*dx2*s12 + 2*dx2*s23 -
                    2*dx3*s23 + dx1*ep*s12*s23 -
                    2*dx2*ep*s12*s23 + dx3*ep*s12*s23 +
                    2*(dx1 - dx2)*ep*c12*c12 +
                    2*(-dx2 + dx3)*ep*c23*c23 -
                    2*dx1*ep*s12*s12 +
                    2*dx2*ep*s12*s12 +
                    2*dx2*ep*s23*s23 -
                    2*dx3*ep*s23*s23))/4.;
        r[2] =  (A*(c2*c23*dx2*ep - c23*c3*dx3*ep -
                    dx2*ep*s2*s23 + dx3*ep*s2*s23 +
                    2*dx3*s3 + dx2*ep*s23*s3 -
                    dx3*ep*s23*s3) +
                 2*ep*(c12*c23*(-dx1 + dx2)*ep +
                    (dx2 - dx3)*
                     (s23*(2 + ep*s12 - 2*ep*s23) +
                       2*ep*c23*c23)))/4.;
    }
    return r;
}

