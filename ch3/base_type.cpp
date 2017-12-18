//
// Created by Guanqi Yu on 11/23/17.
//

#include <iostream>
#include <string>
#include <vector>

int reused = 42;

/**
 * Default: const object only valid in the current source file. Same name in variable files will
 * be replaced by compiler with their corresponding values.
 *
 * if share between multiple files, add extern on both declaration and defination
 */
extern const int bufsize = 42;

using namespace std;

int main() {

	int reused = 10;
	cout << ::reused << endl; // global variable

	double ld = 3.1415926;
//	int a{ld}; // wrong, possible lose information
	int c(ld), d = ld;// correct

	// internal variable(not class) is not initialized when defined in the method
	std::string empty; // initialized

	// variable can be only defined once, but declared multiple times (separate compilation)

	// base type + declarator = compound type
	int *p1 = nullptr; // literal value, c++11
	int *p2 = NULL; // <cstdlib>

	/** reference is not a object, its another name for the existing object
	reference has to be initialized, and cant rebind
	1. type match   2. the init value is an object, not literal value
	 **/

	int *p = nullptr;
	int *&r = p; // a reference to the pointer
	// read from right to left to figure out the exact meaning

	// const object can't change after created, so has to initialize

	const int ci = 1024;
	const int &r1 = ci;
//	int &r2 = ci; // wrong
	const int &r2 = ci * 2;
	/** cant change ld through r3, but ld can be changed **/
	const double &r3 = ld;


	double dval = 3.14;
	const int &ri = dval;
	/** compiler does this: **/
	const int temp = dval;
	const int &rii = temp;

	/** pointer to const v.s. const pointer **/
	const double pi = 3.14;
	const double *pip = &pi;
	/** cant change ld through pip, but ld can be changed **/
	pip = &ld;

	/** top-level const v.s. low level const **/

	// let compiler to validate if a variable's initial value is a const expression
	// only declare constexpr when you are very sure the variable is a const expression(compile time calc)
	// then replace all occurance. different than const variable, which is a variable.
	constexpr int mf = 20; /** must literal value **/
//	constexpr int sz = size(); /** might not constexpr **/

	const int *pa = nullptr; // pointer to const
	constexpr  int *qa = nullptr; // const pointer, constexpr do the top-level const

	typedef char *pstring;
	/** cstr is a const pointer point to char, the base type here is pstring, not const char **/
	const pstring cstr = 0; // same as above

	auto b = ci; // ignore top level const, b is a int
	auto e = &ci; // e is a pointer to const int
	auto &g = ci; // g is a const int reference
	const auto &j = 42; // fine, c++ doesn't allow:   int &a = 7 ---> non-const reference refer to a const value

	/** want use expression type to define the variable, but not use the value to initialize **/
//	decltype(f()) sum = x;
	decltype(ci) x = 0; // x is a const int, compared with auto.
	p = &reused;
	decltype(*p) ca = reused; // the expression is dereference, decltype gives reference type, so must init
	decltype((reused)) da = reused; // add paranthesis, also reference

}//
// Created by Guanqi Yu on 12/8/17.
//

