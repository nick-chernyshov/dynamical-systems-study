//---------------------------------------------------------------------------

#ifndef paramsH
#define paramsH
//---------------------------------------------------------------------------
#include "build_consts.h"
#include <array>

template <size_t P_size>
struct 	params : public std::array<double, P_size> {

    params(double initVal)
    {
        fill(initVal);
    }

    params(params & p)
    {
        memcpy(data(), p.data(), sizeof(double)*size());
    }

    params()
    {
        fill(0.0);
    }

    params & operator = (params<P_size> par) {
        memcpy(data(), par.data(), sizeof(double)*size());
		return * this;
	}
	params & operator = (double x) {
        fill(x);
		return * this;
    }
};
#endif
