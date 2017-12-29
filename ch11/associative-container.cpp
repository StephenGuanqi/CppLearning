//
// Created by Guanqi Yu on 12/28/17.
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

using namespace std;

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{ return lhs.isbn() == rhs.isbn(); }

pair<string, int> process(const vector<string> &v) {
	if (!v.empty())
		return {v.back(), v.back().size()}; // or make_pair
	else
		return pair<string, int>();
};

const string &transform(const string &s, const map<string, string> &m) {
	/**
	 * can't use subscription because passed in map is a const
	 */
	auto map_it = m.find(s);
	if (map_it != m.cend())
		return map_it->second;
	else
		return s;
}

map<string, string> buildMap(ifstream &map_file) {
	map<string, string> trans_map;
	string key, value;
	while (map_file >> key && getline(map_file, value))
		if (value.size() > 1)
			trans_map[key] = value.substr(1);
		else
			throw runtime_error("no rule for " + key);
	return trans_map;
};

void word_transform(ifstream &map_file, ifstream &input) {
	auto trans_map = buildMap(map_file);
	string text;
	while (getline(input, text)) {
		istringstream stream(text);
		string word;
		bool firstword = true;
		while (stream >> word) {
			if (firstword)
				firstword = false;
			else
				cout << " ";
			cout << transform(word, trans_map);
		}
		cout << endl;
	}
}

size_t hasher(const Sales_data &d) {
	return hash<string>()(d.isbn());
}

bool eqOp(const Sales_data &lhs, const Sales_data &rhs) {
	return lhs.isbn() == rhs.isbn();
}

int main() {
	/**
	 * All associative container:
	 * doesn't support push_back push_front    iterators are bidirectional
	 * initializ a map   {key, value}   map's elements are pairs
	 * pair<t1,t2> p = {.., ..}
	 * for_each can be used for map
	 */
	map<string, string> authors = { {"a", "b"}, {"c", "d"}};

	std::map<std::vector<int>::iterator, int> mv;
	std::map<std::list<int>::iterator, int> ml; // list iterator no < operator, but can be declared

	std::vector<int> vi;
	mv.insert(pair<std::vector<int>::iterator, int>(vi.begin(), 0));

	// but when using this one the compiler complained that
	// error: no match for 'operator<' in '__x < __y'
//	std::list<int> li;
//	ml.insert(pair<std::list<int>::iterator, int>(li.begin(), 0));

	/**
	 * declare using function pointer type, define passed in function pointer
	 * when elems added in, invoke the compareIsbn to sort the elems
	 */
	multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);
	using less = bool (*)(Sales_data const&, Sales_data const&);
	multiset<Sales_data, less> bookstore2(compareIsbn);

	/**
	 * pair's default constructor initialized the data member
	 * p1 < p2    p1.first < p2.first || p1.first == p2.first && p1.second < p2.second
	 */
	pair<string, size_t> word_count_pair;  // "",0
	pair<string, string> author{"James", "Tom"}; // also provide initializer


	map<string, size_t> word_count = { {"James", 2} };
	auto map_it = word_count.begin(); // map<string, size_t>::value_type, is a pair
//	map_it->first = "test"; the key is const
	map_it->second = 3; // map<string, size_t>::mapped_type can be changed
	/**
	 * set iterator only has const iterator, can never change the key value(key_type or value_type) through iterator
	 */

	/**
	 * dictionary order. When use iterator to iterate map, multimap, set or multiset,
	 * iterator iterate the elements according to key's ascending order
	 */
	while (map_it != word_count.cend()) {
		cout << map_it->first << " occurs " << map_it->second << "times" << endl;
	}

	/**
	 * we usually don't use generic algorithm on associative container.
	 * 1. write algo don't work  --->  set all elems const, map pair first elem const
	 * 2. read algorithm needs search, which is sequential search, which is very slow.
	 * e.g. find---> sequential search for key  O(n), but map.find  very fast
	 * normally we use the ac as a input source or destination in generic algo
	 */
	multiset<string> c; vector<string> v;
	copy(v.begin(), v.end(), inserter(c, c.end())); // legal
//	copy(v.begin(), v.end(), back_inserter(c)); // illegal, no `push_back` in `set`.
	copy(c.begin(), c.end(), inserter(v, v.end())); // legal.
	copy(c.begin(), c.end(), back_inserter(v)); // legal.

	/**
	 * set
	 * constructor    set(vec.cbegin(), vec.cend())   or set = {...}
	 * insert         set.insert(vec.cbegin(), vec.cend())  or set.insert({....})
	 */
	word_count.insert({"Tom", 3});


	string word;
	while (cin >> word) {
		auto ret = word_count.insert({word, 1}); // pair<map<string,size_t>::iterator, bool>
		if (!ret.second) ++ret.first->second;
	}
	/**
	 * erase    key or iterator
	 */
	word_count.erase("Tom");

	/**
	 * only map has subscript operation. set, multimap, unordered_map doesn't have
	 * if the key doesn't exist when using subscript, automatically insert a new initialized element
	 * map["Anna"] = 1
	 * 1. find key, not found   2. create a pair with key const string and initialized value 0
	 * 3. get out the new elem and assign mapped value 1
	 */
	while (cin >> word)
		++word_count[word];

	// sometimes we just need find
	if (word_count.find("foobar") == word_count.cend())
		cout << "cant find" << endl;

	/**
	 * for multimap and multiset, elems with same key will be stored together
	 */
	multimap<string, size_t> authorss;
	string search_item = "test";
	auto entries = authorss.count(search_item);
	auto iter = authorss.find(search_item);
	while (entries) {
		cout << iter->second << endl;
		++iter;
		--entries;
	} // or another way to do this (get an iterater range)
	for (auto begin = authorss.lower_bound(search_item), end = authorss.upper_bound(search_item);
			begin != end; ++begin) {
		cout << begin->second << endl;
	} // or the 3rd way
	for (auto pos = authorss.equal_range(search_item); pos.first != pos.second; ++pos.first)
		cout << pos.first->second << endl;


	/**
	 * upper_bound return iterator point to the last position match the specific key
	 * lower_bound return iterator point to the first position match the key
	 */
	std::vector<int> data = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };
	auto lower = std::lower_bound(data.begin(), data.end(), 4);
	auto upper = std::upper_bound(data.begin(), data.end(), 4);
	std::copy(lower, upper, std::ostream_iterator<int>(std::cout, " ")); // 4 4 4

	/**
	 * string s; cin >> s
	 * s will ignore all white space tab line, and read from the first char to last char
	 * getline read entire line including \n from the stream
	 * store in string object, \n is ignored
	 * a empty line --> ""
	 */


	ifstream ifs_map("../data/word_transformation_bad.txt"), ifs_content("../data/given_to_transform.txt");
	if (ifs_map && ifs_content) word_transform(ifs_map, ifs_content);
	else std::cerr << "can't find the documents." << std::endl;

	/**
	 * unordered associative container    use hash function and == to organize elements rather than <
	 * stl provide hash template for internal type(including pointer), string, smart pointer
	 * use own version class as key must provide hash template version
	 * Search, Insert, Remove operations should have average-case constant runtime
	 */
	using SD_multiset = unordered_multiset<Sales_data, decltype(hasher)*, decltype(eqOp)*>;
	SD_multiset bookStore(42, hasher, eqOp); // 42 is bucket size
	// if class defined == operator, we can only overloading hash function
	// unordered_set<Foo, decltype(FooHash)*> fooSet(10, FooHash);

	/**
	 * [] can only used in non-const map or unordered_map
	 */
}