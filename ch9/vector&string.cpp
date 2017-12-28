//
// Created by Guanqi Yu on 12/27/17.
//

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include <array>
#include <stack>
#include "../ch7/Sales_data.h"

using namespace std;

void test() {
	/**
	 * increase capacity: reserve(n)     capacity may be n or greater     (vector, string)
	 * decrease capacity: shrink_to_fit     stl don't guarantee shrink    (deque, string, vector)
	 * increase/decrease elems num: resize (sequential container except for array)
	 */

	/**
	 * list and array don't have capacity member function
	 * list does not hold elements contiguously. array has the fixed size statically.
	 */
	string s = "hello world";
	string subs = s.substr(6); // world
	/**
	 * substr return s from pos n's char's copy
	 * if pos+n > s.length()  only copy to s's end character
	 */
	vector<char> v{ 'p', 'e', 'z', 'y' };
	string str(v.cbegin(), v.cend());

	/**
	 * npos is const string::size_type, value -1, which is the biggest possible size of size_type
	 * find return size_type
	 */
	string name("AnnaBelle");
	auto pos1 = name.find("Anna"); // case sensitive
	if (pos1 != string::npos)
		cout << pos1 << endl;

	string numbers("0123456789");
	name = "r2d2";
	auto pos2 = name.find_first_of(numbers); // 1
	name = "03472p2";
	auto pos3 = name.find_first_not_of(numbers); // 5

	string::size_type pos = 0;
	while ((pos = name.find_first_of(numbers, pos)) != string::npos) {
		cout << "found number at index: " << pos
             << "element is " << name[pos] << endl;
		++pos; // important to avoid infinite loop
	}

	string river("Mississippi");
	auto first_pos = river.find("is"); // 1
	auto last_pos = river.rfind("is"); // 4
	// string also have find_last_of

	string s2 = "pi = 3.14";
	auto d = stod(s2.substr(s2.find_first_of("+-.0123456789"))); // 3.14

	/**
	 * three sequential container adapter:
	 * stack, queue, priority_queue
	 * an adapter can make something behave like other thing
	 *
	 * support:
	 * size_type, value_type, container_type
	 * empty size swap
	 * A a; A a(c)
	 */
	deque<char> deq(s.begin(), s.end());
	stack<char> stk(deq); // initialize an adapter with the container
	stack<char, vector<char>> stk2(v);
	/**
	 * stack: constructed by any container except for array and forward_list   (only need push/pop back and back)
	 * queue: constructed by list or deque, not vector                         (push back, pop front, front/back)
	 * priority_queue: vector or deque                                         (push back, pop back, random access)
	 */
}