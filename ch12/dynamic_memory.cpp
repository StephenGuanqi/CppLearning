//
// Created by Guanqi Yu on 12/29/17.
//

#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iterator>
#include <list>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <functional>
#include <sstream>
#include "../ch7/Sales_data.h"
#include <memory>

using namespace std;

int main() {
	/**
	 * shared pointer's usage is similar to smart pointer, but it automatically release the object it points to
	 * the safest way to use and allocate dm is through make_share
	 *
	 * make_share similar to emplace, use parameter to construct the specific type
	 */
	shared_ptr<string> p1;
	if (p1 && p1->empty())  *p1 = "hi";

	shared_ptr<int> p2 = make_shared<int>(42);
	auto p3 = make_shared<string>(10, '9');

	/**
	 * when copy or assign, every shared_ptr record how many other shared_ptr point to same object (reference count)
	 * when one shared_ptr is assigned new value or leave the function scope, reference count decrease
	 */
	auto q(p2); // q point to same object as p, object has two reference count

	/**
	 * Once a shared_ptr's reference count is zero, it automatically release the managed object
	 * 1. r point to new object   2. increase *q object reference count   3. decrease original *r rc  4.release
	 */
	auto r = make_shared<int>(42);
	r = q;

	/**
	 * shared pointer can record how many shared pointer point to the same object
	 * and it can release the object at some specific time. (see above)
	 * it will call destructor to release and also release the associative memory
	 *
	 * If u put shared_ptr in a container and in some point u just want to use some elements of the container,
	 * use erase to erase the no need pointer elems
	 */

	/**
	 * three reasons to use dynamic memory:
	 * 1. program don't know how much objects we need     (container class)
	 * 2. program don't know the exact type of needed objects
	 * 3. program needs to shared data across multiple objects
	 */
	vector<string> v1;
	{
		vector<string> v2 = {"a", "an", "the"};
		v1 = v2;
		/**
		 * v2 destroyed, elements inside destroyed, v1 has v2's copy
		 */
	}


}