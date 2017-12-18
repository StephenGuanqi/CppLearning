//
// Created by Guanqi Yu on 12/17/17.
//

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>

using namespace std;

int main() {
	// use size_type has to specified which type it is defined from
	// string can use directly, but vector object always contains the template type
	using sz = vector<int>::size_type;
//	vector::size_type ; //wrong

	/**
	 * only vector, string, deque, array support < > operator for iterator
	 * others like list don't have <
	 * so iterate container usually use != to judge the ending criterion
	 */

	list<string> a = {"million", "test", "shit"};
	list<string>::iterator it1 = a.begin();
	list<string>::const_iterator it2 = a.begin();
	auto it3 = a.begin(); // only when a is a const, it3 is a const iterator
	auto it4 = a.cbegin(); // always const iterator

	vector<const char*> articles = {"a", "b"};
	list<string> b(a);
//	deque<string> c(a);// wrong, container and elements type must match
	/**
	 * use iterator to copy, container can be different, element also can be different iff can transformed
	 */
	forward_list<string> words(articles.begin(), articles.end());

	/**
	 * map container doesn't have size parameter, only sequential container(except for array) has
	 * array container has to specify size when declared, because the size is fixed and we cant insert or delete
	 * array container can be copied, but built-in array doesn't support copy
	 */

}