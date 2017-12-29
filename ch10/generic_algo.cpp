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
#include <forward_list>
#include <functional>

using namespace std;

bool isShorter(const string &s1, const string &s2) {
	return s1.size() < s2.size();
}

void elimDumps(vector<string> &words) {
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	/**
	 * when no duplicate, end_unique = words.end()
	 */
	words.erase(end_unique, words.end());
}

void biggies(vector<string> &words, vector<string>::size_type sz) {
	elimDumps(words);
	stable_sort(words.begin(), words.end(),
				[] (const string &a, const string &b)
				{ return a.size() < b.size(); });
	// acquire an iterator point to the first elem satisfying size() >= sz
	auto wc = find_if(words.begin(), words.end(),
				[sz] (const string &a)
				{ return a.size() >= sz; });
	auto count = words.end() - wc;
	cout << count << " ";
	/**
	 * for_each apply callable object on each elements in input sequence. unary predicate
	 * for_each can't use cbegin or cend
	 */
	for_each(wc, words.end(), [] (const string &s) { cout << s << " "; });
	cout << endl;
}

/**
 * No size order or dictionary order
 */
void biggies_partition(vector<string> &words, vector<string>::size_type sz) {
	elimDumps(words);
	auto pivot = partition(words.begin(), words.end(),
				[sz] (const string &s) { return s.size() >= sz; });
	for_each(words.begin(), pivot, [] (const string &s) { cout << s << " "; });
}


bool check_size(const string &s, string::size_type sz) {
	return s.size() >= sz;
}
ostream &print(ostream &os, const string &s, char c) {
	return os << s << c;
}
/**
 * No size order
 */
void biggies_stable_partition(vector<string> &words, vector<string>::size_type sz,
								ostream &os = cout, char c = ' ') {
	elimDumps(words);
	auto pivot = stable_partition(words.begin(), words.end(), [sz] (const string &s) {
		return s.size() >= sz;
	});
	auto pivot2 = stable_partition(words.begin(), words.end(),
							bind(check_size, placeholders::_1, sz));


	for_each(words.begin(), pivot, [&os, c] (const string &s) {
		os << s << c;
	});
	for_each(words.begin(), pivot, [&, c] (const string &s) {
		os << s << c;
	});
	for_each(words.begin(), pivot, [=, &os] (const string &s) {
		os << s << c;
	});
	for_each(words.begin(), words.end(), bind(print, ref(os), placeholders::_1, ' '));
}

void fnc() {
	/**
	 * lambda capture: value capture and reference capture
	 * to use value capture, the object must can be copied
	 *
	 * if a function return lambda collable object, it can't contains reference capture.
	 *
	 * to mix use implicit and explicit capture, the first argument in the list must be & or =
	 */
	size_t v1 = 42;
	auto f = [v1] { return v1; }; // copy capture
	v1 = 0; auto j = f(); // 42

	size_t v2 = 42;
	auto f2 = [&v2] { return v2; };; // reference capture
	v2 = 0; j = f2(); // 0;
}



void transform_test() {
	std::string s("hello");
	std::transform(s.begin(), s.end(), s.begin(),
	               [](unsigned char c) -> unsigned char { return std::toupper(c); });

	std::vector<size_t> ordinals;
	std::transform(s.begin(), s.end(), std::back_inserter(ordinals),
	               [](unsigned char c) -> size_t { return static_cast<size_t>(c); });
}

void for_each_test() {
	std::vector<int> nums{3, 4, 2, 8, 15, 267};

	auto print = [](const int& n) { std::cout << " " << n; };

	std::cout << "before:";
	std::for_each(nums.begin(), nums.end(), print);
	std::cout << '\n';

	std::for_each(nums.begin(), nums.end(), [](int &n){ n++; });

	std::cout << "After:";
	std::for_each(nums.begin(), nums.end(), print);
	std::cout << '\n';
}


void test() {
	int ia[] = {27, 210, 12, 47, 19, 5, 5, 83};
	int val = 83;
	int *result = find(begin(ia), end(ia), val);

	vector<int> vec(begin(ia), end(ia));
	val = 42;
	auto result2 = find(vec.begin(), vec.end(), val);
	if (result2 != vec.cend())   cout << "find!" << endl;

	cout << count(vec.begin(), vec.end(), 5) << endl;
	/**
	 * remove removes all elems(val). find find first elem(val) in range. replace replace all elems.
	 * find_if accept predicate    remove_if accept predicate  count_if also predicate    ---> unary
	 */

	/*********************read only algorithm*******************************/
	int sum = accumulate(vec.begin(), vec.end(), 0);
	/**
	 * the third argument decide which + operator to use and what is the return type
	 * use cbegin and cend for read-only algoeithm
	 */
	vector<string> vecstr;
	string sumstr = accumulate(vecstr.cbegin(), vecstr.cend(), string(""));
	// string sumstr = accumulate(vecstr.cbegin(), vecstr.cend(), ""); // wrong because const char * don't have + operator
	vector<double> vd = { 1.1, 0.5, 3.3 };
	sum = accumulate(vd.cbegin(), vd.cend(), 0); // result here is 4

	vector<string> roster1; list<string> roster2;
	equal(roster1.cbegin(), roster1.cend(), roster2.cbegin()); // assume roster2 equal or longer than roster1



	/********************* write operation *******************************/
	fill(vec.begin(), vec.end(), 0);
	/**
	 * generic algorithm can't change the underlying size of container because it doesn't do container operation
	 * like insertion or deletion, so algorithm can never directly add or remove elements
	 * only operate on passed in iterators
	 */
	vec = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	fill_n(vec.begin(), vec.size(), 0);
	vec.clear();
	fill_n(vec.begin(), vec.size(), 0); // fine
	fill_n(vec.begin(), 10, 0); // disaster

	vec.clear();
	auto it = back_inserter(vec);
	*it = 42;   // equal to invoke push_back

	vec.clear();
	fill_n(back_inserter(vec), 10, 0); // no problem

	int a1[] = {0, 1, 2, 3, 4, 5};
	int a2[sizeof(a1) / sizeof(*a1)];
	auto ret = copy(begin(a1), end(a1), a2); // ret is a pointer for a2 tail elem's next position

	/**
	 * multiple algorithm has copy version that not operate on the original list
	 */
	replace(vec.begin(), vec.end(), 0, 42);
	vector<int> vec_copy;
	replace_copy(vec.begin(), vec.end(), back_inserter(vec_copy), 0, 42); // vec doesn't change, works on vec_copy


	vec.clear();
	list<int> lst;
	int i;
	while (cin >> i)
		lst.push_back(i);
	copy(lst.cbegin(), lst.cend(), back_inserter(vec));


	vector<int> v;
	v.reserve(10);
	fill_n(v.begin(), 10, 0);
	// ^ (b)No error, but not any sense. v.size() still equal zero.
	// Fixed: 1. use `v.resize(10);`
	//    or  2. use `fill_n(std::back_inserter(v), 10, 0)`

	vector<string> words = {"dda", "ewqe", "ada", "qweqwewq"};
	elimDumps(words);
	stable_sort(words.begin(), words.end(), isShorter); // same length words remain original order
	/**
	 * sort ---> binary predicate
	 * find_if ---> unary predicate
	 */

	/*************************Lambda  ***************************/

	/**
	 * Four types of callable objects:
	 * Function, pointer to function, class that overloads the "()", lambda expression
	 *
	 * Lambda expression: capture list and function body is a must
	 * 1. return type is void when no specify return type
	 * 2. no default arguments. # of xing can always == # of shi can
	 * 3. capture list only works on local non-static variable, lambda can directly use local static variable
	 * and variable defined outside the function
	 * 4. when a lambda is passed in, a new class type and that object are creates,
	 * capture list become member of the class and being initialized when lambda object is created
	 * 5. if function body only one line return, the return type can be ignored. If includes other lines, compiler
	 * think the lambda returns void
	 *
	 * when to use:
	 * generic algorithm. small lines ---> lambda
	 * multiple lines ---> function
	 * multiple parameters ---> lambda + capture lists OR function with parameter binding
	 */
	auto f = [] { return 42; };
	cout << f() << endl;
	stable_sort(words.begin(), words.end(),
	            [] (const string &a, const string &b)
	                { return a.size() < b.size(); });

	transform(v.begin(), v.end(), v.begin(), [](int i) { return i < 0 ? -i : i; });
	transform(v.begin(), v.end(), v.begin(), [](int i) {
		/**
		 * wrong, compiler think the lambda returns void, but it actually returns int
		 */
		if (i < 0)  return -i; else return i;
	});
	transform(v.begin(), v.end(), v.begin(),
	          [](int i) -> int
	          { return i < 0 ? -i : i; }); // right

	/**
	 * parameter binding
	 * bind function is a general function adapter
	 * unbound arguments can be deemed as reference to the parent callable
	 * arguments to bind (sz, os, etc.) pass by value or reference (copy capture, reference capture)
	 */
	auto newCallable = bind(check_size, placeholders::_1, 6);
	string s = "hello";
	bool b1 = newCallable(s);

	sort(words.begin(), words.end(), isShorter);
	sort(words.begin(), words.end(), bind(isShorter, placeholders::_2, placeholders::_1));

}

bool predicate(const std::string &s)
{
	return s.size() >= 5;
}

void testPartition() {
	auto v = std::vector<std::string>{ "a", "as", "aasss", "aaaaassaa", "aaaaaabba", "aaa" };
	auto pivot = std::partition(v.begin(), v.end(), predicate);

	for (auto it = v.cbegin(); it != pivot; ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}