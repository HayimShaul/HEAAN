/*
* Copyright (c) by CryptoLab inc.
* This program is licensed under a
* Creative Commons Attribution-NonCommercial 3.0 Unported License.
* You should have received a copy of the license along with this
* work.  If not, see <http://creativecommons.org/licenses/by-nc/3.0/>.
*/
#include "Plaintext.h"

Plaintext::Plaintext(ZZ* mx, long logp, long logq, long N, long n) : mx(mx), logp(logp), logq(logq), N(N), n(n) {

}

Plaintext::~Plaintext() {
	if (mx) delete[] mx;
}
