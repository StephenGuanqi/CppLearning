//
// Created by Guanqi Yu on 11/23/17.
//

#include <iostream>
#include <string>
#include <cctype>
#include <vector>

int reused = 42;

extern const int bufsize = 42; // add extern to share the const variable among multi files

using namespace std;

int main() {

    // header can't has using declaration

	/**
	 * Copy initialize: use = to initialize
	 * Direct initialize: not use =
	 * **/

	string s1; // empty string
	string s2(s1); // direct initialize
	string s3 = "test"; // copy initialize

	string s4(10, 'c'); // or
	s4 = string(10, 'c');
	// equals to
	string temp(10, 'c');  s4 = temp;

	// size() return a string::size_type, which is an unsigned (we don't know how long exactly)
	auto len = s4.size(); // unsigned long
	/** whe an expression contains size(), then don't use int, avoid issue of int and unsigned **/

	s1 = s3 + s4;
//	s2 = "hello" + "."; // wrong, must have a string on sides of +
	s2 = s1 + "hello" + ","; // (s1 + "hello")
	/** the literal string is not std::string, is a C string which is char array stop by '\0' **/


	/**
	 For code like is >> s, input is separated by whitespaces while reading into string s.
	 For code like getline(is, s) input is separated by newline \n while reading into string s. Other whitespaces are ignored.
	 **/
	for(string str; cin >> str; cout << str << endl);
	for(string str; getline(cin, str); cout << str << endl);

	string str;
	for (string buf; cin >> buf; str += (str.empty()? "" : " ") + buf);


	/**
	 * Let compiler decide the type of c
	 */
	string s("Hello World");
	decltype(s.size()) punct_cnt = 0;
	for (auto c : s)
		if (ispunct(c))
			++punct_cnt;
	for (auto &c : s)
		c = toupper(c);


	/**
	 * Assign an out of range value to an unsigned type, result is mod
	 * Assign an out of range value to an signed type, result is undefined
	 * []'s input is a string::size_type, unsigned type, so if passed in an signed type, auto changed to unsigned type
	 * but the value still [0, s.size()), or undefined behaviour
	 */
	for (decltype(s.size()) index = 0; index != s.size() && !isspace(s[index]); index++)
		s[index] = toupper(s[index]);
	// always set subscript to string::size_type, so it will not be less than zero, than we just check it is less than size()

	str = ("a simple string");
	for(decltype(s.size()) i = 0; i != s.size(); i++)
		str[i] = 'X';

	string s0;
	cout << s0[0] << endl; // undefined behaviour



	const string sc = "Keep out!";
	for(auto &c : sc) {
		cout << c;
//		c = 'X';// c is a const char &
	}
}