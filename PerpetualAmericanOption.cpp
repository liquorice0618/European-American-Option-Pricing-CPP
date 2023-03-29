// PerpetualAmericanOption.cpp
// A class of American options, drived from Option class


#include <vector>
#include <cmath>
#include "PerpetualAmericanOption.hpp"

using namespace std;



// ====================================================================================================

// Kernal functions
double PerpetualAmericanOption::CallPrice(double U) const
{
	double y1 = 0.5 - b / (sig * sig) + sqrt((b / (sig * sig) - 0.5) * (b / (sig * sig) - 0.5) + 2 * r / (sig * sig));	// calculate y1
	double C = (K / (y1 - 1)) * pow((y1 - 1) * U / y1 / K, y1);
	return C;
}

double PerpetualAmericanOption::PutPrice(double U) const
{
	double y2 = 0.5 - b / (sig * sig) - sqrt((b / (sig * sig) - 0.5) * (b / (sig * sig) - 0.5) + 2 * r / (sig * sig));	// calculate y1
	double P = (K / (1 - y2)) * pow((y2 - 1) * U / y2 / K, y2);
	return P;
}


// ======================================================================================================

// Constructor

// Default constructor
PerpetualAmericanOption::PerpetualAmericanOption() : Option()
{
	optClass = "PerpetualAmerican";
}

// Initializing constructor
PerpetualAmericanOption::PerpetualAmericanOption(double r_val, double sig_val, double K_val, double T_val, double b_val, string optType_val, string unam_val) : Option(r_val, sig_val, K_val, T_val, b_val, optType_val, unam_val, "PerpetualAmerican")
{
}

// Copy constructor
PerpetualAmericanOption::PerpetualAmericanOption(const PerpetualAmericanOption& option2) : Option(option2)
{
}


// Destructor
PerpetualAmericanOption::~PerpetualAmericanOption()
{
}


// Overloading operator
PerpetualAmericanOption& PerpetualAmericanOption::operator = (const PerpetualAmericanOption& option2)
{
	if (this == &option2)	// avoid self-assigning
	{
		return *this;
	}
	Option::operator = (option2);

	return *this;
}




// =======================================================================================

// Functions that calculate option price

// calculate the option price
double PerpetualAmericanOption::Price(double U) const
{
	if (optType == "C")
	{
		return CallPrice(U);	// calculate the price of call
	}
	else
	{
		return PutPrice(U);		// calculate the price of put
	}
}


// calculate the option price
vector<double> PerpetualAmericanOption::Price(vector<double> vecU) const
{
	vector<double> vecPrice;		// the vector of option price
	for (vector<double>::iterator it = vecU.begin(); it != vecU.end(); it++)
	{
		vecPrice.push_back(Price(*it));		// add each price to the price vector
	}

	return vecPrice;				// return the price vector
}


