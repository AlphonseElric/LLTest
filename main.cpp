#include "stdafx.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <mpir.h>
#include <mpirxx.h>

using namespace std;

bool LLTest(unsigned int p) {
	mpz_t s;
	mpz_init(s);
	mpz_set_ui(s, 4);

	mpz_t m;
	mpz_init(m);
	mpz_ui_pow_ui(m, 2, p);
	mpz_sub_ui(m, m, 1);

	for (int i = 0; i < (p - 2); i++) {
		mpz_pow_ui(s, s, 2);
		mpz_sub_ui(s, s, 2);
		mpz_mod(s, s, m);
		if (i != 0 && i % 10000 == 0) {
			cout << "Increment " << i << "/" << (p - 2) << " calculated." << endl;
		}
	}

	if (mpz_cmp_ui(s, 0) == 0) {
		return true;
	} else {
		return false;
	}

}

int main(int argc, char *argv[])
{
	if (argc != 2 || atoi(argv[1]) < 3) {
		cout << "Usage: " << argv[0] << " exponent" << endl << endl;
		cout << "The exponent must be an odd prime!" << endl;
		cout << "Larger exponents will take a long time to calculate." << endl;
		return 0;
	}
	
	cout << "[Irrational's Lucas-Lehmer Tester]" << endl;
	cout << "Testing exponent P=" << argv[1] << "..." << endl;

	unsigned int p = stoul(argv[1], nullptr, 10);

	if (LLTest(p) == true) {
		cout << "Congratulations! Exponent P=" << argv[1] << " is a Mersenne Prime!" << endl;
		cout << "If this is not a known Mersenne Prime, you may be entitled to a cash prize!" << endl;
		cout << "Visit http://www.mersenne.org for more information!" << endl;
	} else {
		cout << "Exponent P=" << argv[1] << " is not a Mersenne Prime. Try again!";
	}

    return 0;
}

