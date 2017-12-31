#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

string::size_type find_char(const string &s, char c,
                            string::size_type &occurs) {
	auto ret = s.size();
	occurs = 0;
	for (decltype(ret) i = 0; i != s.size(); i++) {
		if (s[i] == c) {
			if (ret == s.size())
				ret = i;
			++occurs;
		}
	}
	return ret;
}

void print(const int *begin, const int *end) {
	while (begin != end) {
		cout << *begin++ << endl;
	}
}

// const int ia[] equals to const int ia*
void print2(const int ia[], size_t size) {
	for (size_t i = 0; i < size; i++) {
		cout << ia[i] << endl;
	}
}

// has to be sure of length of array, argument is array reference
/**
 * only way to know exact length of passed in array
 * if const int[10], it only express how long we expect, the actual value not necessarily 10
 * so it's just a pointer
 */
void print3(int (&arr)[10]) {
	for (auto elem : arr) {
		cout << elem << endl;
	}
}

void error_msg(initializer_list<string> ls) {
	for (auto begin = ls.begin(); begin != ls.end(); ++begin) {
		cout << *begin << endl;
	}

	for (const auto &elem : ls) {
		cout << elem << endl;
	}
}

/**
 * Decrease the overhead of function invocation
 * define inline to let compiler unfold/expand the code
 * compiler might ignore the request of inline (such as inline recursive function)
 * and also!!: inline and constexpr function in the header file!
 */
inline const string &
shorterStringConst(const string &s1, const string &s2) {
	return s1.size() < s2.size() ? s1 : s2;
}

/**
 * change unconst parameters to const version, and then cast the return back to unconst version
 * usage of const cast + overload
 * @param str
 * @param ix
 * @return
 */
string &shorterString(string &s1, string &s2) {
	auto &r = shorterStringConst(const_cast<const string&>(s1),
							const_cast<const string&>(s2));
	return const_cast<string&>(r);
}

char &get_val(string &str, string::size_type ix) {
	return str[ix];
}

vector<string> process() {
	string expect = "expect";
	string actual = "hahah";
	if (expect.empty())
		return {};
	else if (expect == actual)
		return {"functionX", "okay"};
	else
		return {"functionX", "expected", "actual"};
	/**
	 * list initialized return value!!!!
	 * container can be copied
	 * but array cant be copied, so a function can't return an array
	 */

	/**
	 * but we can return array pointer
	 * int (*func(int i))[10]
	 * or
	 * auto func(int i) -> int(*)[10]
	 * or
	 * int odd[] = {1, 2, 3}
	 * decltype(odd) *arrPtr(int i) {
	 *      ....
	 * }
	 * auto and decltype usage here can also be applied to the pointer to function
	 */
}

int main() {

	/**
	 * can't copy array to pass into the function
	 * only in the pointer form
	 */
	int j[2] = {1, 2};
	print(begin(j), end(j));

	/**
	 * use const reference as possible as you can, or:
	 * can't passed in const object, can't passed in literal value
	 * for string::size_type, can alsp passed in as reference
	 */

	/**
	 * objects in initializer list are always always const, we can never change the value in list
	 * use condition: we dont know how much parameters we need for the function
	 * if all parameters same type: so use initializer_list
	 * if not: changeable parameter template
	 */
	initializer_list<string> ls;
	string expect = "expect";
	string actual = "hahah";
	if (expect != actual) {
		error_msg({"functionX", expect, actual});
	} else {
		error_msg({"function", "okay"});
	}

	/**
	 * the return value in a function should never be local variable's pointer or reference (unless malloc, can't return local string)
	 * return reference should be return a variable that already exist before the function start
	 * return reference is left value
	 */
	get_val(expect, 2) = 'c';
//	string &item = string("hi");
//	shorterString(string("hi"), string("bye")) = "X"; // wrong, lvaue reference can't band to rvalue expression
	string s1 = "hi"; string s2 = "bye";
	shorterString(s1, s2) = "X";

	/**
	 * Function Overloading: function-matching ---> overload resolution
	 * No local declaration of function, otherwise previous declaration will be overwrite
	 */

	/**
	 * const overloading:
	 * top level const in parameter diff is not function overloading
	 * if parameter is pointer or reference, low-level const can be overloaded
	 */

	/**
	 * default argument function declaration put in the header file, one function only declared once
	 */

	/**
	 * inline function and const expression function must be defined in header files
	 * because if multiple source file has different definition, then when unfolded will have different behaviour
	 */

	/**
	 * preprocessor variable like NULL and assert do not belong to namespace, managed by preprocessor
	 * if NDBUG is defined, nothing happen to assert
	 */
#ifndef NDEBUG
	cerr << __func__ << "array size is :" << expect.size() << endl;
#endif


	/**
	 * if function has default argument, point it out in the function declaration, not function defination
	 * also put declaration in header file
	 * typedef string::size_type sz;
	 * string screen(sz, sz, char = ' ');
	 * string screen(sz, sz, char = '*'); // wrong
	 * string screen(sz = 24, sz = 80, char); //right
	 */

}

