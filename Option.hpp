// Option.hpp
// A base class for all different options

#ifndef OPTION_HPP
#define OPTION_HPP

#include<string>
#include<iostream>

using namespace std;

class Option
{
public:
	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Expiry time
	double b;		// Cost of carry

	string optType;	// Option name (call, put)
	string unam;	// Name of underlying asset
	string optClass;// Option class: "European" or "PerpetualAmerican"

	// Constructor
	Option();		// default constructor
	Option(double r_val, double sig_val, double K_val, double T_val, double b_val, string optType_val, string unam_val, string optClass_val);		// initialing constructor
	Option(const Option& option2);		// copy constructor

	// Destructor
	virtual ~Option();
	
	// Overloading operator
	Option& operator = (const Option& option2);		// assignment operator

	// Functions that calculate option price and sensitivities
	virtual double Price(double U) const;
	virtual double Delta(double U) const;
	virtual double Gamma(double U) const;
	virtual double Delta(double U, double h) const;		// numerical delta
	virtual double Gamma(double U, double h) const;		// numerical gamma

	// Modifier
	void toggle();		// Change option type (C/P, P/C)

};



#endif // !OPTION_HPP
