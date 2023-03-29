// EuropeanOption.hpp
// A class of plain options, drived from Option class

#ifndef EUROPEANOPTION_HPP
#define EUROPEANOPTION_HPP

#include "Option.hpp"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class EuropeanOption : public Option
{
private:
	// 'Kernel' functions for option calculations
	double CallPrice(double U) const;
	double PutPrice(double U) const;
	double CallDelta(double U) const;
	double CallGamma(double U) const;
	double PutDelta(double U) const;
	double PutGamma(double U) const;

public:
	// Constructor
	EuropeanOption();		// default constructor
	EuropeanOption(double r_val, double sig_val, double K_val, double T_val, double b_val, string optType_val, string unam_val);	// initializing constructor
	EuropeanOption(const EuropeanOption& option2);		// copy constructor

	// Destructor
	virtual ~EuropeanOption();

	// Overloading operator
	EuropeanOption& operator = (const EuropeanOption& option2);		// assignment operator

	// Functions that calculate option price and sensitivities
	double Price(double U) const;				// calculate the option price
	double Delta(double U) const;				// calculate the option delta
	double Gamma(double U) const;				// calculate the option gamma
	double Delta(double U, double h) const;		// numerical calculate the option delta
	double Gamma(double U, double h) const;		// numerical calculate the option gamma

	vector<double> Price(vector<double> vecU) const;	// option price vector
	vector<double> Delta(vector<double> vecU) const;	// option delta vector
	vector<double> Gamma(vector<double> vecU) const;	// option gamma vector

	double PCP_Price(double U) const;			// calculate call and put prices from each other using put-call parity relationship
	bool SatisfyPCP(double call_price, double put_price, double U) const;	// check if the PCP is satisfied

};






#endif // !EUROPEANOPTION_HPP
