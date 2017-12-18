//
// Created by Guanqi Yu on 12/17/17.
//

#ifndef CPPPRIMER_ACCOUNT_H
#define CPPPRIMER_ACCOUNT_H

#include <iostream>

/**
 * 1. static member cant be const, also cant use this in the function
 * 2. generally speaking we cant initialized static member inside the class. conversely, we define and initialize
 * every static member outside the class, and only defined once. (similar to golbal variable, always exist in the
 * program's life cycle)
 * 3. When static member is constexpr, we can do in-class initialize using const
 */
class Account {
public:
	void calculate() { amount += amount * interestRate; }
	static double rate() { return interestRate; }
	static void rate(double);
private:
	std::string owner;
	double amount;

	static double interestRate;
	static constexpr double todayRate = 42.42;
	static double initRate();

	static constexpr int period = 30;
	double daily_tbl[period];

	static Account test1; // static member can be incomplete type
	Account *test2; // pointer member can be incomplete type
//	Account test3; // error, data member must be complete type
};


#endif //CPPPRIMER_ACCOUNT_H
