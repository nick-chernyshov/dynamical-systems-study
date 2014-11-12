//---------------------------------------------------------------------------
#ifndef stateH
#define stateH
//---------------------------------------------------------------------------
#include "build_consts.h"

#include <array>

template<size_t S_size>
struct state : public std::array<double, S_size>{
	
    state(double x) {
        std::array<double, S_size>::fill(x);
	}
	state() {
        state(0.0f);
	}

    state & operator = (double x) {
        std::array<double, S_size>::fill(x);
        return *this;
    }
    state & operator = (state<S_size> & a) {

        memcpy(data(), a.data(), S_size*sizeof(double));
        return * this;
    }

	state & operator -= (double a) {
        for (size_t i=0; i<S_size; i++)
            operator[](i) -= a;
		return * this;
    }
    state & operator -= (state<S_size> a) {
        for (size_t i=0; i<S_size; i++)
            operator[](i) -= a[i];
		return * this;
    }
	state & operator += (double a) {
        for (size_t i=0; i<S_size; i++)
            operator[](i) += a;
		return * this;
    }
    state & operator += (state<S_size> a) {
        for (size_t i=0; i<S_size; i++)
            operator[](i) += a[i];
		return * this;
    }
	state & operator *= (double a) {
        for (size_t i=0; i<S_size; i++)
            operator[](i) *= a;
		return * this;
    }
	state & operator /= (double a) {
        a = 1.0f/a;
        operator *=(a);
		return * this;
    }

	state & operator %= (double a) {
		a = abs(a);
        for (int i = 0; i < S_size; i++) {
            while (operator[](i) > a*0.5) {
                operator[](i) -= a;
			}
            while (operator[](i) < -a*0.5) {
                operator[](i) += a;
			}
		}
		return * this;
    }

	state operator / (double a) {
		a = 1.0/a;
        state<S_size> x;
		x = (*this) * a;
		return x;
	}

	state operator * (double a) {
        state<S_size> x;
        for (size_t i = 0; i < S_size; i++)
            x[i] = operator [](i)*a;
		return x;
	}

    state operator + (state<S_size> a) {
        a += *this;
		return a;

	}

    state operator - (state<S_size> a) {
        a-=*this;
        return a;
	}

    double operator * (state<S_size> & a)
	{
		double sum = 0;
        for (size_t i = 0; i < S_size; i++) {
            sum += operator [](i) * a[i];
		}
		return sum;
	}

};
template<size_t S_size>
state<S_size> operator * (double a, state<S_size> b)
{
    for(auto & it : b)
        it *= a;
    return b;
}

#endif

