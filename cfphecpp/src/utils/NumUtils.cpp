#include "NumUtils.h"

#include <cassert>
#include <cmath>

void NumUtils::sampleGauss(ZZX& res, long& d, double& stdev) {
	static double const Pi=4.0*atan(1.0); // Pi=3.1415..
	static long const bignum = 0xfffffff;
	// THREADS: C++11 guarantees these are initialized only once

	if(d<=0) {
		d=deg(res)+1;
	}
	if (d<=0) {
		return;
	}
	res.SetMaxLength(d); // allocate space for degree-(n-1) polynomial
	for(long i=0; i<d; i++) {
		SetCoeff(res, i, ZZ::zero());
	}

	// Uses the Box-Muller method to get two Normal(0,stdev^2) variables
	for (long i=0; i<d; i+=2) {
		double r1 = (1+RandomBnd(bignum))/((double)bignum+1);
		double r2 = (1+RandomBnd(bignum))/((double)bignum+1);
		double theta=2*Pi*r1;
		double rr= sqrt(-2.0*log(r2))*stdev;

		assert(rr < 8*stdev); // sanity-check, no more than 8 standard deviations

		// Generate two Gaussians RV's, rounded to integers
		long x = (long) floor(rr*cos(theta) +0.5);
		SetCoeff(res, i, x);
		if (i+1 < d) {
			x = (long) floor(rr*sin(theta) +0.5);
			SetCoeff(res, i+1, x);
		}
	}
	res.normalize(); // need to call this after we work on the coeffs
}

void NumUtils::sampleGauss(CZZX& res, long& d, double& stdev) {
	sampleGauss(res.rx, d, stdev);
	sampleGauss(res.ix, d, stdev);
}

void NumUtils::sampleZO(ZZX& res, long& d, double& rho) {
	res.SetMaxLength(d);
	ZZ temp;
	long i;
	for (i = 0; i < d; ++i) {
		RandomBits(temp, 2);
		if(temp == 0) {
			SetCoeff(res, i, 1);
		} else if (temp == 1) {
			SetCoeff(res, i, -1);
		} else {
			SetCoeff(res, i, 0);
		}
	}
}

void NumUtils::sampleZO(CZZX& res, long& d, double& rho) {
	res.ix = ZZX::zero();
	ZZ temp;
	long i;
	for (i = 0; i < d; ++i) {
		RandomBits(temp, 2);
		if(temp == 0) {
			SetCoeff(res.rx, i, 1);
		} else if (temp == 1) {
			SetCoeff(res.rx, i, -1);
		} else {
			SetCoeff(res.rx, i, 0);
		}
	}
}

void NumUtils::sampleUniform(ZZX& res, long& d, ZZ& bnd) {
	if (d<=0) d=deg(res)+1; if (d<=0) return;
	if (bnd <= 0) {
		clear(res);
		return;
	}
	res.SetMaxLength(d); // allocate space for degree-(n-1) polynomial
	ZZ ubnd, tmp;
	ubnd =  2*bnd + 1;
	for (long i = 0; i < d; i++) {
		RandomBnd(tmp, ubnd);
		tmp -= bnd;
		SetCoeff(res, i, tmp);
	}
	res.normalize();
}

void NumUtils::sampleUniform(CZZX& res, long& d, ZZ& bnd) {
	sampleUniform(res.rx, d, bnd);
	sampleUniform(res.ix, d, bnd);
}

void NumUtils::sampleUniform2(ZZX& res, long& d, long& logBnd) {
	if (d<=0) d=deg(res)+1; if (d<=0) return;
	res.SetMaxLength(d); // allocate space for degree-(n-1) polynomial
	ZZ tmp;
	for (long i = 0; i < d; i++) {
		RandomBits(tmp, logBnd);
		SetCoeff(res, i, tmp);
	}
	res.normalize();
}

void NumUtils::sampleUniform2(CZZX& res, long& d, long& logBnd) {
	sampleUniform2(res.rx, d, logBnd);
	sampleUniform2(res.ix, d, logBnd);
}
