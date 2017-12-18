//
// Created by Guanqi Yu on 12/17/17.
//

#include "Account.h"

// define and initialize a static member. initRate is in the class scope.
double Account::interestRate = initRate();

void Account::rate(double newRate) {
	interestRate = newRate;
}

double Account::initRate() {
	interestRate = todayRate;
	return interestRate;
}