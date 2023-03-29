// Option.cpp
// A base class for all different options

#include "Option.hpp"
#include <cmath>
#include <iostream>

using namespace std;

// Constructor

// default constructor
Option::Option(): r(0.05), sig(0.2), K(110.0), T(0.5), b(0.05), optType("C"), unam("")
{
}

// initializing constructor
Option::Option(double r_val, double sig_val, double K_val, double T_val, double b_val, string optType_val, string unam_val, string optClass_val)
{
	r = r_val;
	sig = sig_val;
	K = K_val;
	T = T_val;
	b = b_val;
	optType = optType_val;
	unam = unam_val;
	optClass = optClass_val;
}

// copy constructor
Option::Option(const Option& option2)
{
	r = option2.r;
	sig = option2.sig;
	K = option2.K;
	T = option2.T;
	b = option2.b;
	optType = option2.optType;
	unam = option2.unam;
}


// Destructor
Option::~Option()
{
}


// Overloading operator
Option& Option::operator = (const Option& option2)
{
	if (this == &option2)	// avoid self-assigning
	{
		return *this;
	}
	r = option2.r;
	sig = option2.sig;
	K = option2.K;
	T = option2.T;
	b = option2.b;
	optType = option2.optType;
	unam = option2.unam;

	return *this;
}


// Functions that calculate option price and sensitivities
double Option::Price(double U) const
{
	return 0;
}

double Option::Delta(double U) const
{
	return 0;
}

double Option::Gamma(double U) const
{
	return 0;
}

double Option::Delta(double U, double h) const
{
	return (Price(U + h) - Price(U - h)) / (h * 2);		// numerical delta
}

double Option::Gamma(double U, double h) const
{
	return (Price(U + h) + Price(U - h) - Price(U) * 2) / (h * h);		// numerical gamma
}



// Modifier functions

// Change option type (C/P, P/C)
void Option::toggle()
{ 

	if (optType == "C")
		optType = "P";
	else
		optType = "C";
}
