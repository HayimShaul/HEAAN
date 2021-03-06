/*
* Copyright (c) by CryptoLab inc.
* This program is licensed under a
* Creative Commons Attribution-NonCommercial 3.0 Unported License.
* You should have received a copy of the license along with this
* work.  If not, see <http://creativecommons.org/licenses/by-nc/3.0/>.
*/
#include "Ciphertext.h"

#include <NTL/tools.h>
#include "Common.h"

Ciphertext::Ciphertext(ZZ* ax, ZZ* bx, long logp, long logq, long N, long n) :
		ax(ax), bx(bx), logp(logp), logq(logq), N(N), n(n) {

}

void Ciphertext::copy(const Ciphertext &o) {
	assert(o.ax != NULL);
	assert(o.bx != NULL);

	clean();

	logp = o.logp;
	logq = o.logq;
	N = o.N;
	n = o.n;
	ax = new ZZ[N];
	bx = new ZZ[N];
	for (long i = 0; i < N; ++i) {
		ax[i] = o.ax[i];
		bx[i] = o.bx[i];
	}
}

void Ciphertext::clean() {
	if (ax != NULL)
		delete[] ax;
	ax = NULL;

	if (bx != NULL)
		delete[] bx;
	bx = NULL;
}
