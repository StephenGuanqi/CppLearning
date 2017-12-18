//
// Created by Guanqi Yu on 12/16/17.
//

#include "Sales_data.h"
#include "Account.h"

using namespace std;

int main() {
	Sales_data total(std::cin);
	if (!total.isbn().empty())
	{
		std::istream &is = std::cin;
		while (is) {
			Sales_data trans(is);
			if (total.isbn() == trans.isbn())
				total.combine(trans);
			else {
				print(std::cout, total) << std::endl;
				total = trans;
			}
		}
		print(std::cout, total) << std::endl;
	}
	else
	{
		std::cerr << "No data?!" << std::endl;
		return -1;
	}

	Sales_data item;
	string null_book = "test";

//	Sales_data data = null_book;
	Sales_data data2 = cin;
	/**
	 * Implicit converting constructor: one parameter, one step, direct/copy initialization
	 * it is a implicit constructor that can be invoked use one parameter. it implicitly changes
	 * the parameter type to the class type.
	 * explicit constructor can only be used for direct initialization
	 */

	Sales_data data3(null_book);
//  item.combine("test"); // wrong, two step
//	item.combine(string("test")); // wrong, explicit
// 	item.combine(null_book); // wrong, explicit
	item.combine(cin);
	item.combine(Sales_data("test"));
	item.combine(static_cast<Sales_data>(null_book)); // static_cast can use explicit constructor

	/**
	 * vector<T> vec(n)   ---> explicit
	 * string s("value");
	 * string s = "value";  ----> not explicit
	 */


	double r = Account::rate();

	return 0;
}