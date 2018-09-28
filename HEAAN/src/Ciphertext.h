/*
* Copyright (c) by CryptoLab inc.
* This program is licensed under a
* Creative Commons Attribution-NonCommercial 3.0 Unported License.
* You should have received a copy of the license along with this
* work.  If not, see <http://creativecommons.org/licenses/by-nc/3.0/>.
*/
#ifndef HEAAN_CIPHERTEXT_H_
#define HEAAN_CIPHERTEXT_H_

#include <NTL/ZZ.h>

#include <fstream>

using namespace std;
using namespace NTL;

class Ciphertext {
public:

	ZZ* ax;
	ZZ* bx;

	long logp;
	long logq;

	long N;
	long n;

	Ciphertext(ZZ* ax = NULL, ZZ* bx = NULL, long logp = 0, long logq = 0, long N = 0, long n = 0);

	Ciphertext(const Ciphertext* o);

	virtual ~Ciphertext();
	
};

#endif
