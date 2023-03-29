// PerpetualAmericanOption.hpp
// A class of American options, drived from Option class

#ifndef AMERICANOPTION_HPP
#define AMERICANOPTION_HPP

#include "Option.hpp"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class PerpetualAmericanOption : public Option
{
private:
	// 'Kernel' functions for option calculations
	double CallPrice(double U) const;
	double PutPrice(double U) const;

public:
	// Constructor
	PerpetualAmericanOption();		// default constructor
	PerpetualAmericanOption(double r_val, double sig_val, double K_val, double T_val, double b_val, string optType_val, string unam_val);	// initializing constructor
	PerpetualAmericanOption(const PerpetualAmericanOption& option2);		// copy constructor

	// Destructor
	virtual ~PerpetualAmericanOption();

	// Overloading operator
	PerpetualAmericanOption& operator = (const PerpetualAmericanOption& option2);		// assignment operator

	// Functions that calculate option price and sensitivities
	double Price(double U) const;				// calculate the option price
	vector<double> Price(vector<double> vecU) const;	// option price vector
};






#endif
