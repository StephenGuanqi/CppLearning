//
// Created by Guanqi Yu on 12/27/17.
//

#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <iterator>
#include <fstream>
#include <forward_list>
#include <functional>
#include "../Sales_item.h"

using namespace std;

void test2() {
	/**
	 * insert iterator
	 * insert iterator is an adapter for iterator
	 * *it = val   (inserter)
	 * equals to:
	 * it = c.insert(it, val); ++it;   --> increase it to make it point to original elem
	 *
	 * front_inserter different from inserter, always insert in the front (use push_front)
	 * back_inserter use push_back (make sure the container supports corresponding operations)
	 */
	list<int>   lst = {1, 2, 3, 4};
	list<int> lst2, lst3;
	copy(lst.cbegin(), lst.cend(), front_inserter(lst2)); // 4 3 2 1
	copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin())); // 1 2 3 4

	std::vector<int> vec{ 1, 1, 3, 3, 5, 5, 7, 7, 9 };
	lst.clear();
	std::unique_copy(vec.begin(), vec.end(), back_inserter(lst));

	/**
	 * stream iterator
	 */
	istream_iterator<int> int_it(cin);
	istream_iterator<int> int_eof; // off the tail iterator
	while (int_it != int_eof)
		vec.push_back(*int_it++);
	// or
	istream_iterator<int> in_iter(cin), eof;
	vector<int> vecit(in_iter, eof);
	// generic algorithm
	istream_iterator<int> in(cin);
	cout << count(in, eof, 0) << endl;

	ostream_iterator<int> out_iter(cout, " "); // no off the tail, 2nd param must be c-style string
	for (auto e : vec)
		*out_iter++ = e;
	// or more precise
	copy(vec. begin(), vec.end(), out_iter);
	cout << endl;

	ifstream ifs("../data");
	istream_iterator<string> inf_it(ifs), infeof;
	vector<string> vecs(inf_it, infeof); // in
	copy(vecs.cbegin(), vecs.cend(), ostream_iterator<string>(cout, " ")); // out

	istream_iterator<Sales_item> ins_iter(cin), in_eof;
	vector<Sales_item> sales_vec;
	copy(ins_iter, in_eof, back_inserter(sales_vec));
	sort(sales_vec.begin(), sales_vec.end(), compareIsbn);
	for (auto begin = sales_vec.cbegin(), end = begin; begin != sales_vec.cend(); begin = end) {
		end = find_if(begin, sales_vec.cend(), [begin] (const Sales_item &item)
		{ return item.isbn() != begin->isbn(); });
		cout << accumulate(begin, end, Sales_item(begin->isbn())) << endl;
	}

	/**
	 * reverse iterator
	 * all containers support reverse iterator except for forward list (forward iterator doesn't supoort --)
	 * ++ makes a reverse iterator move to previous elem, -- makes a revers iterator move forward
	 */
	sort(vec.begin(), vec.end()); // ascending
	sort(vec.rbegin(), vec.rend()); // descending

	string line = "FIRST, MIDDLE, LAST";
	auto rcomma = find(line.cbegin(), line.cend(), ',');
//	cout << string(line.crbegin(), rcomma) << endl;
	cout << string(rcomma.base()) << endl;

	/**
	 * Generic algorithm required iterators' category:
Input iterators : ==, !=, ++, *, ->   (read only)
Output iterators : ++, *   (Input Iterator's opposite, write only)
Forward iterators : ==, !=, ++, *, ->    (read and write)
Bidirectional iterators : ==, !=, ++, --, *, ->
Random-access iterators : ==, !=, <, <=, >, >=, ++, --, +, +=, -, -=, -(two iterators), *, ->, iter[n] == * (iter + n)

copy : first and second are Input iterators, last is Output iterators.
reverse : Bidirectional iterators.
unique : Forward iterators.

	 */

	/**
	 * ALG(beg, end, dst, args)
	 * assume no matter how much elems, it is safe to write in dst
	 * dst could be output iterator  --->  insert_iterator or ostream_iterator
	 *
replace(beg, end, old_val, new_val); // replace the old_elements in the input range as new_elements.
replace_if(beg, end, pred, new_val); // replace the elements in the input range which pred is true as new_elements.
replace_copy(beg, end, dest, old_val, new_val); // copy the new_elements which is old_elements in the input range into dest.
replace_copy_if(beg, end, dest, pred, new_val); // copy the new_elements which pred is true in the input range into dest.

	 */
	remove_if(vec.begin(), vec.end(), [](int i) {
		return i % 2;
	});
	vector<int> v2;
	remove_copy_if(vec.begin(), vec.end(), back_inserter(v2),
		[](int i) { return i % 2; });

	/**
	 * for list and forwardlist, use the member function algorithm first rather than generic algorithm
	 * sort needs random access iterators, list has bidirectional iterator, forward_list has forward iterator
	 * algorithm in generic type doen't change underlying container, list change
	 * e.g. merge
	 */


	/**
	 * generic algorithm never and never change the size of the sequence they are doing. They move elems from one place
	 * to another, but never insert or deletion.
	 * But insertion, however, can be done by insert_iterator
	 * forward_list and lists' own algos will modify the conainer(including size)
	 */
}


void remove_odds(forward_list<int>& flist)
{
	auto is_odd = [] (int i) { return i & 0x1; };
	remove_if(flist.begin(), flist.end(), is_odd);
}

auto strip(string& str) -> string const&
{
	for (auto& ch : str) ch = tolower(ch);
	str.erase(remove_if(str.begin(), str.end(), [] (char ch) { return ispunct(ch); }), str.end());
	return str;
}


int main() {
	/**
	 * Removes all elements satisfying specific criteria from the range [first, last) and returns a
	 * past-the-end iterator for the new end of the range.
	 * Removing is done by shifting (by means of move assignment) the elements in the range in such a way that the elements
	 * that are not to be removed appear in the beginning of the range. Relative order of the elements that remain is preserved
	 * and the physical size of the container is unchanged.
	 *
	 * RETURN pass-the-end iterator for the new range
	 */
	list<int> list = {1, 2, 3, 4, 5};
	vector<int> vec(list.begin(), list.end());
	auto f = [] (int i) { return i & 0x1; };
	list.remove_if(f);
	copy(list.cbegin(), list.cend(), ostream_iterator<int>(cout, " "));
	cout << "list size: " << list.size() << endl;

	auto pos = remove_if(vec.begin(), vec.end(), f);
	for_each(pos, vec.end(), [](const int &i) { cout << i << " "; });
	cout << "vec size: " << vec.size() << endl;

	std::string str1 = "Text with some   spaces";
	str1.erase(std::remove(str1.begin(), str1.end(), ' '),
	           str1.end());
	std::cout << str1 << '\n';

}