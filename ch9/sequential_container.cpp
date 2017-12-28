//
// Created by Guanqi Yu on 12/17/17.
//

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include <array>
#include "../ch7/Sales_data.h"

using namespace std;

int main() {
	// use size_type has to specified which type it is defined from
	// string can use directly, but vector object always contains the template type
	using sz = vector<int>::size_type;
//	vector::size_type ; //wrong

	/**
	 * only vector, string, deque, array support < > , iter += n -= n  iter1 - iter2 operator
	 * others like "list" and "forward_list" don't have <
	 * so iterate container usually use != to judge the ending criterion
	 * list iterator supports ++ and --
	 */

	/**
	 * array: fixed size, fast random access
	 * deque: fast random access, similar to vector except fast insert and delete in two ends, and will not allocate new space
	 * list: has to traverse to get specific alems. iterator supports ++ and --, fast insert and delete
	 */


	list<string> a = {"million", "test", "shit"};
	list<string>::iterator it1 = a.begin();
	list<string>::const_iterator it2 = a.begin();
	auto it3 = a.begin(); // only when a is a const, it3 is a const iterator
	auto it4 = a.cbegin(); // always const iterator
	/**
	 * All containers all template class
	 * difference_type  is a unsigned integer type storing the distance between two container; value_type  element type
	 * All containers:
	 * Constructor: C c; C c1(c2); C c(b, e);  C c{a, b, c...}
	 * Assignment: c1 = c2;  c1 = {a, b, c...}
	 * insert erase emplace
	 *
	 * Only Sequential Containers:
	 * C seq(n); C seq(n, t)
	 */
	list<string>::iterator iter;
	vector<int>::difference_type count;


	/**
	 * initialized a container as another container's copy
	 */
	vector<const char*> articles = {"a", "b"};
	list<string> b(a);
//	deque<string> c(a);// wrong, container and elements type must match
	/**
	 * use iterator to copy, container can be different, element also can be different iff can transformed
	 */
	forward_list<string> words(articles.begin(), articles.end());


	/**
	 * list initialization, explicitly define every element, implicitly define container's size
	 */
	list<string> authors = {"a", "b", "c"};

	/**
	 * map container doesn't have size parameter in constructors, only sequential container(except for array) has
	 * array container has to specify size when declared, because the size is fixed and we cant insert or delete
	 * array container can be copied, but built-in array doesn't support copy
	 */
	array<int, 42>::size_type i;
//	array<int>::size_type j;// wrong, array<int> is not a type
	array<int, 10> ia1;
	array<int, 10> ia2 = {0, 1, 2, 3};
	array<int, 10> copy = ia2;
	ia2 = {1, 2, 3, 4};


	list<string> names;
	vector<const char*> oldstyles;
	names.assign(oldstyles.cbegin(), oldstyles.cend()); // can't name=oldstyles
	list<string> slist(1);
	slist.assign(10, "Hi");
	// equals to: slist.clear(); slist.insert(slist.begin(), 10, "Hi");
	/**
	 * assign(not for array and associative container) will lead left container's iterators, references, pointers all invalid
	 * swap changes nothing except for string and array
	 */


	/**
	 * all containers accept == and != operations
	 * all containers except for non-order container accept < > <= >= operations
	 * forward_list supports max_size and empty, but not size function
	 */
	std::list<int>      li{ 1, 2, 3, 4, 5 };
	std::vector<int>    vec2{ 1, 2, 3, 4, 5 };
	cout << (vector<int>(li.begin(), li.end()) == vec2 ) << endl;

	/**
	 * aLL sequential containers:
	 * push_back  emplace_back  pop_back   (not for forward_list)
	 * push_front emplace_front pop_front  (not for vector and string)
	 * insert
	 *
	 * insertion makes vector, string, deque makes all reference, iterators, pointers invalid, and all of them are time consuming
	 * because for vector ans string, it moves the elements, or allocate new space and copies
	 */
	list<unsigned> l{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	deque<unsigned> odd, even;
	for (auto i : l)
		(i & 0x1 ? odd : even).push_back(i);

	/**
	 * Important: elements in the container are copy.
	 * No matter we initialized a container using object or insert object, the elem is a copy
	 * we change the elem in container has no effect for the original object
	 */
	vector<Sales_data> c;
	c.emplace_back(); // default constructor of Sales_data
	c.emplace_back("99999"); // string constructor

	/**
	 * no matter invoke front & back or begin & end iterator
	 * has to check if the container is empty, otherwise undefined behaviour
	 */
	if (!a.empty()) {
		// value copy here
		auto last = a.end(); auto val = *(--last); // forward_list can't - on iterator
		auto val2 = a.back(); // forward_list don't support. array has no front.
	}
	/**
	 * front, back, subscript, at return reference
	 */
	if (!a.empty()) {
		a.back() = 42;
		auto &v = a.back(); v = "42";
	}

	/**
	 * also make sure the container is not empty before u pop_front or pop_back
	 * erase one elem or range erase both return the next elem's iterator
	 */
	auto it = l.begin();
	while (it != l.end())
		if (*it % 2)
			it = l.erase(it);
		else
			it++;
	l.erase(l.begin(), l.end()); // equals to l.clear()
	// l.erase(it1, it2); after delete, it1 = it2
	// if before erase, it1 = it2, nothing happen

	/**
	 * forwardlist: insert/erase_after insert/delete elem after some elem
	 * lst.before_begin() return the off-the-beginning iterator to insert before head
	 */
	forward_list<int> flst(l.begin(), l.end());
	auto prev = flst.before_begin();
	auto current = flst.begin();
	while (current != flst.end()) {
		if (*current % 2)
			current = flst.erase_after(prev);
		else {
			prev = current;
			current++;
		}
	}

	/**
	 * If use resize to shrink the container, all iterator, reference and pointers point to the deleted element is not effective
	 * vector, string, deque resize may lead to all iterator, reference and pointers lose effect
	 * insert and deletion may also lead losing effect
	 * especially for vector, string and deque, after insertion and deletion must update iterator
	 */
	vector<int> vi = {0, 1, 2, 3, 4, 5};
	auto iterator = vi.begin();
	while (iterator != vi.end()) {
		if (*iterator % 2) {
			iterator = vi.insert(iterator, *iterator);
			iterator += 2;
		} else
			iterator = vi.erase(iterator);
	}
	/**
	 * end can't be stored, must invoked everytime
	 */
}

void removeEvenAndDoubleOdds(list<int> &data) {
	for (auto iter = data.begin(); iter != data.end(); ) {
		if (*iter % 2) {
			iter = data.insert(iter, *iter);
//			iter += 2;
			advance(iter, 2);
		} else
			iter = data.erase(iter);
	}
}

void removeEvenAndDoubleOdds(forward_list<int> &data) {
	for (auto prev = data.before_begin(), current = data.begin(); current != data.end(); ) {
		if (*current % 2) {
			current = data.insert_after(prev, *current);
			/**
			 * be careful about how much step we add to avoid the infinite loop (current never reach end())
			 * never assume the current value after insertion. Could be anything ---> lose effect!
			 */
			advance(prev, 2);
			advance(current, 2);
		} else
			current = data.erase_after(prev);
	}
}

