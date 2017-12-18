//
// Created by Guanqi Yu on 12/16/17.
//

#include "Sales_data.h"

using namespace std;

Sales_data& Sales_data::combine(const Sales_data &rhs) {
	units_sold += rhs.units_sold; // units_sold and revenue are governed by implicit this
	revenue += rhs.revenue;
	return *this; // can call the function concatenate
}

istream &read(istream &is, Sales_data &item) {
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}

// call like print(print(cout, data1), data2)
ostream &print(ostream &os, const Sales_data &item) {
	os << item.isbn() << " " << item.units_sold << " "
        << item.revenue << " " << item.avg_price();
	return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
	Sales_data sum = lhs; // default copy is data member
	sum.combine(rhs);
	return sum;
}

//Sales_data::Sales_data(const std::string &s, unsigned cnt, double price) {
//	// provided this contructor is not defined in the class
//	bookNo = s;
//	units_sold = cnt;
//	revenue = cnt * price;
//	/**
//	 * two phases: since no constructor initialize list, all member default initialized first
//	 * then assign them with three values
//	 */
//}

class ConstRef {
public:
	ConstRef(int ii);
private:
	int i;
	const int ci;
	int &ri;
};
//ConstRef::ConstRef(int ii) { // wrong, ci and ri must be initialized
//	i = ii;
//	ci = ii;
//	ri = i;
//}
ConstRef::ConstRef(int ii) : i(ii), ci(ii), ri(ii) {}
// initialize order is actually the order that members are defined
// in class, not the order in initialize list
// warning: binding reference member 'ri' to stack allocated parameter 'ii'