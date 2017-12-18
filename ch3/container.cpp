//
// Created by Guanqi Yu on 11/23/17.
//

#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

int main() {
	/**
	 * For iterator, its object is container's element or char in string
	 * valid iterator point to either some elems or the next position of the end elem
	 * all other conditions are invalid iterator
	 */

	vector<string> v;
	auto b = v.begin(), e = v.end(); // e is off the end iterator
	cout << (b == e) << endl; // true, b and e are the same iterator, which is end iterator

	string s("something");
	if (s.begin() != s.end()) { // s not empty
		auto it = s.begin();
		(*it) = toupper(*it);
	}

	// cant' do ++ or dereference on end(), because end doesn't actually point to an elem
	for (auto it = s.begin(); it != s.end() && !isspace(*it); it++)
		*it = toupper(*it);

	/**
	 * coding style of != works on all std provided container
	 * some container like string and vector has subscript, so can use non-iterator with < size
	 * but container without subscript only use iterator, and most of iterator hasn't defined < operator
	 */

	vector<int> vn;
	const vector<int> vc;
	auto it = vn.cbegin();
	auto itc = vc.cbegin(); // both condition returns const_iterator

	vector<string> text;
	for (string line; getline(cin, line); text.push_back(line));
	for (auto &line :text)
		for (auto &ch : line)
			if (isalpha(ch))
				ch = toupper(ch);

	string target = "tar";
	auto beg = text.begin(), end = text.end();
	auto mid = beg + (end - beg) / 2;           // cant beg + end, no meaning
	while (beg != end && *mid != target) {
		if (target < *mid)
			end = mid;
		else
			beg = mid + 1;
		mid = beg + (end - beg) / 2;
	}

}

// print content of a vector
void print_content(const vector<string> &vec) {
	cout << "size:" << vec.size() << ", content: [";
	for(auto it = vec.cbegin(); it != vec.cend(); it++)
		cout << (*it) << (it != vec.cend() - 1 ? ", " : "");
	cout << "]" << endl;
}