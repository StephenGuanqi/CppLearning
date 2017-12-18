//
// Created by Guanqi Yu on 12/8/17.
//

#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

int main() {
	// ++ -- is prior than dereference
	vector<int> vin(10);
	auto pbeg = vin.begin();
	while (pbeg != vin.end() && *pbeg > 0) {
		cout << *pbeg++ << endl; // good way
	}

	/**
	 * Strong recommend bit manipulation only on unsigned type
	 * If bit manipulation exist, use unsigned
	 * */
	int ia[10];
	constexpr size_t sz = sizeof(ia) / sizeof(*ia);

	/**
	 * in most situations, type that is smaller than int will first upgrade to bigger type
	 */
	unsigned char bits = 0233;
	bits << 8; // integral promotion, implicit conversion

	int j = 0; double i = 6.0;
	double slope = static_cast<double>(j) / i;

	int *ip;
	char *pc = reinterpret_cast<char*>(ip);

	// const_cast change the low level const
	const char *pc2;
	char *p = const_cast<char*>(pc2);
	// if the object is not a const, then it's legal to obtain write permission

}