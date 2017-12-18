//
// Created by Guanqi Yu on 12/16/17.
//

#ifndef CPPESSENTIAL_SALES_DATA_H
#define CPPESSENTIAL_SALES_DATA_H

#include <iostream>

/**
 * 1. never use 'using' declaration in a header file
 * 2. declare all friends together at the class beginning or end
 * 3. all member public, use struct, otherwise use class
 * 4. compiler first compile members declaration, then compile function body
 * 5. class related non-member functions, declare in header, not definition
 * 6. synthesized default constructor ---> in-class initializer or default initializer
 * 7. compiler will only create default constructor when there is no constructor definition
 * 8. If your compiler doesn't support in-class initializer, use constructor initialize list
 * 9. construct, assign(copy), deconstruct, compiler will generate three versions for the class to
 * deal with every member of the class  (vector and string safer and more efficient)
 */
class Sales_data {
// declare friend for non-member function to access non-public member
friend Sales_data add(const Sales_data&, const Sales_data);
friend std::istream &read(std::istream&, Sales_data&);
friend std::ostream &print(std::ostream&, const Sales_data&);

public:
	// constructor
	Sales_data() = default;
	//Sales_data() : bookNo(""), units_sold(0), revenue(0.0) { }
	explicit Sales_data(const std::string &s) : bookNo(s) { } // prevent implicit converting constructor for
	// constructor that has only one parameters
	Sales_data(const std::string &s, unsigned n, double p) :
				bookNo(s), units_sold(n), revenue(p) { }
	Sales_data(std::istream &is) { read(is, *this); } // default initialized first

	// public member function
	std::string isbn() const { return bookNo; } // const member function
	Sales_data& combine(const Sales_data&);
	inline double avg_price() const;
private:
	std::string bookNo;
	unsigned units_sold = 0; // store integer eg 0, size may be determined by compiler
	double revenue = 0.0;
};

inline
double Sales_data::avg_price() const {
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}

extern Sales_data add(const Sales_data&, const Sales_data&);
extern std::istream &read(std::istream&, Sales_data&);
extern std::ostream &print(std::ostream&, const Sales_data&);


/**
 * isbn implicitly: return this->bookNo     this is a Sales_data *const
 * total.isbn() equals to:
 * Sales_data::isbn(&total)
 *
 * we can't invoke non-const member function on a const object
 * but we can call const member function on a non-const object
 */

/**
 * 1. IO class can't be copied, only pass by reference
 * 2. print function not responsible for new line! reduce the control for output and let user code to decide
 */

/**
 * Sales_data(const std::string &s) : bookNo(s) { }
 * same as:
 * Sales_data(const std::string &s) : bookNo(s), units_sold(0), revenue(0) { }
 */

#endif //CPPESSENTIAL_SALES_DATA_H
