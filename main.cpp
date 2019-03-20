#include <cmath>
#include <cstdlib>
#include <iostream>
#include <future>
#include <thread>
#include <chrono>

#include <mpirxx.h>
#include <mpir.h>

using namespace std;

bool LLTest(unsigned long p)
{
	mpz_t s;
	mpz_init(s);
	mpz_set_ui(s, 4);

	mpz_t m;
	mpz_init(m);
	mpz_ui_pow_ui(m, 2, p);
	mpz_sub_ui(m, m, 1);

	unsigned long i;

	auto handle = async(launch::async, [&]()
	{
		double digitcount = floor(log10(p - 2));
		string s = string(digitcount, ' ');

		cout << "Increment 0" << s << "/" << p - 2 << " done.";
		while (i != (p - 2))
		{
			this_thread::sleep_for(0.5s);
			cout << "\rIncrement " << i;
		}
	});

	for (i = 0; i < (p - 2); i++)
	{
		mpz_pow_ui(s, s, 2);
		mpz_sub_ui(s, s, 2);
		mpz_mod(s, s, m);
	}

	handle.wait();

	return (mpz_cmp_ui(s, 0) == 0 ? true : false);
}

void help()
{
	cout << "Usage: LLTest <exponent>" << endl << endl;
	cout << "The exponent must be an odd prime!" << endl;
	cout << "Larger exponents will take a long time to calculate." << endl;
	return;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		help();
		return 0;
	}

	unsigned long p = strtoul(argv[1], nullptr, 10);

	if (p < 3)
	{
		cout << "Exponent must be an odd prime. Exiting..." << endl;
	}

	cout << "[Irrational's Lucas-Lehmer Tester]" << endl;
	cout << "Testing exponent P=" << p << "..." << endl;

	if (LLTest(p))
	{
		cout << endl << "Congratulations! Exponent P=" << p << " is a Mersenne Prime!" << endl;
		cout << "If this is not a known Mersenne Prime, you may be entitled to a cash prize!" << endl;
		cout << "Visit http://www.mersenne.org for more information!" << endl;
	}
	else
	{
		cout << endl << "Exponent P=" << p << " is not a Mersenne Prime. Try again!";
	}

	return 0;
}

