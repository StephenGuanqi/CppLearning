//
// Created by Guanqi Yu on 11/23/17.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Sales_data {
	std::string bookNo;     /* default initializer */
	unsigned units_sold = 0;
	double revenue = 0.0;   /* in-class initializer */
};

int main() {

	/**
	 * vector is a class template, template is not a class
	 * create with specific type is called instantiation
	 * **/
	// list copy initialization
	vector<string> articles = {"a", "an", "the"};
	// list direct initialization
	vector<string> vs{"a","b"};
	// value initialized, value must have initial value
	vector<int> ivec(10);   // 10 zero
	cout << "ivec[0]:" << ivec[0] << endl;
	vector<string> svec(10);// 10 empty string
	svec = {10, "s"};              // 10 "s"
	vector<string> svec2(10, "s"); // 10 "s", compare with vector<int>

    vector<int> v1(2, 5);
    vector<int> v2{5, 5}; // v2 = {5, 5};
    vector<int> v3(v2);
    cout << (v1 == v2) << " " << (v2 == v3) <<endl; // compare all elements

	//	vector<int>::size_type // correct
	//	vector::size_type //wrong
	//  can't compare vector<Sales_data> because no defined comparision for elem Sales_Data

	/* string manipulation, no need for define size when define vector */
	vector<string> vec;
	for(string word; cin >> word; vec.push_back(word)) ;
	for(auto &str : vec) for(auto &c : str) c = toupper(c);

	for (vector<string>::size_type i; i != vec.size(); i++)
		cout << vec[i] << endl;

	auto size = vec.size();
	for (int i = 0; i != size; i++)
		;

}