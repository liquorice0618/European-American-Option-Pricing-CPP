// EuropeanOption.cpp
// A class of plain options, drived from Option class

#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions.hpp>

#include <vector>
#include <cmath>
#include "EuropeanOption.hpp"

using namespace std;



// ====================================================================================================

// Kernal functions
double EuropeanOption::CallPrice(double U) const
{
	using namespace boost::math;
	normal_distribution<> Normal(0, 1);

	double d1 = (log(U / K) + (b + sig * sig / 2) * T) / (sig * sqrt(T));	// calculate d1
	double d2 = (log(U / K) + (b - sig * sig / 2) * T) / (sig * sqrt(T));	// calculate d2

	double C = (U * exp((b - r) * T) * cdf(Normal, d1)) - (K * exp(-r * T) * cdf(Normal, d2));	// calculate the call price

	return C;
}

double EuropeanOption::PutPrice(double U) const
{
	using namespace boost::math;
	normal_distribution<> Normal(0, 1);

	double d1 = (log(U / K) + (b + sig * sig / 2) * T) / (sig * sqrt(T));	// calculate d1
	double d2 = (log(U / K) + (b - sig * sig / 2) * T) / (sig * sqrt(T));	// calculate d2

	double P = K * exp(-r * T) * cdf(Normal, -d2) - U * exp((b - r) * T) * cdf(Normal, -d1);	// calculate the put price

	return P;
}

double EuropeanOption::CallDelta(double U) const
{
	using namespace boost::math;
	normal_distribution<> Normal(0, 1);

	double d1 = (log(U / K) + (b + sig * sig / 2) * T) / (sig * sqrt(T));	// calculate d1
	
	double dC = exp((b - r) * T) * cdf(Normal, d1);		// calculate the call delta

	return dC;
}

double EuropeanOption::CallGamma(double U) const
{
	using namespace boost::math;
	normal_distribution<> Normal(0, 1);

	double d1 = (log(U / K) + (b + sig * sig / 2) * T) / (sig * sqrt(T));	// calculate d1

	double ddC = (pdf(Normal, d1) * exp((b - r) * T)) / (U * sig * sqrt(T));	// calculate the call gamma

	return ddC;
}

double EuropeanOption::PutDelta(double U) const
{
	using namespace boost::math;
	normal_distribution<> Normal(0, 1);

	double d1 = (log(U / K) + (b + sig * sig / 2) * T) / (sig * sqrt(T));	// calculate d1

	double dP = -exp((b - r) * T) * cdf(Normal, -d1);		// calculate the put delta

	return dP;
}

double EuropeanOption::PutGamma(double U) const
{
	using namespace boost::math;
	normal_distribution<> Normal(0, 1);

	double d1 = (log(U / K) + (b + sig * sig / 2) * T) / (sig * sqrt(T));	// calculate d1

	double ddP = (pdf(Normal, d1) * exp((b - r) * T)) / (U * sig * sqrt(T));	// calculate the put gamma

	return ddP;
}



// ======================================================================================================

// Constructor

// Default constructor
EuropeanOption::EuropeanOption(): Option()
{
	optClass = "European";
}

// Initializing constructor
EuropeanOption::EuropeanOption(double r_val, double sig_val, double K_val, double T_val, double b_val, string optType_val, string unam_val): Option(r_val, sig_val, K_val, T_val, b_val, optType_val, unam_val, "European")
{
}

// Copy constructor
EuropeanOption::EuropeanOption(const EuropeanOption& option2) : Option(option2)
{
}


// Destructor
EuropeanOption::~EuropeanOption()
{
}


// Overloading operator
EuropeanOption& EuropeanOption::operator = (const EuropeanOption& option2)
{
	if (this == &option2)	// avoid self-assigning
	{
		return *this;
	}
	Option::operator = (option2);

	return *this;
}




// =======================================================================================

// Functions that calculate option price and sensitivities

// calculate the option price
double EuropeanOption::Price(double U) const
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

// calculate the option delta
double EuropeanOption::Delta(double U) const
{
	if (optType == "C")
	{
		return CallDelta(U);
	}
	else
	{
		return PutDelta(U);
	}
}

// calculate the option gamma
double EuropeanOption::Gamma(double U) const
{
	if (optType == "C")
	{
		return CallGamma(U);
	}
	else
	{
		return PutGamma(U);
	}
}

// numerical methods of option delta
double EuropeanOption::Delta(double U, double h) const
{
	return (Price(U + h) - Price(U - h)) / (h * 2);
}

// numerical methods of option gamma
double EuropeanOption::Gamma(double U, double h) const
{
	return (Price(U + h) + Price(U - h) - Price(U) * 2) / (h * h);
}




// calculate the option price
vector<double> EuropeanOption::Price(vector<double> vecU) const
{
	vector<double> vecPrice;		// the vector of option price
	for (vector<double>::iterator it = vecU.begin(); it!= vecU.end(); it++)
	{
		vecPrice.push_back(Price(*it));		// add each price to the price vector
	}

	return vecPrice;				// return the price vector
}

// calculate the option delta
vector<double> EuropeanOption::Delta(vector<double> vecU) const
{
	vector<double> vecDelta;		// the vector of option delta
	for (vector<double>::iterator it = vecU.begin(); it != vecU.end(); it++)
	{
		vecDelta.push_back(Delta(*it));		// add each price to the delta vector
	}

	return vecDelta;				// return the delta vector
}

// calculate the option gamma
vector<double> EuropeanOption::Gamma(vector<double> vecU) const
{
	vector<double> vecGamma;		// the vector of option gamma
	for (vector<double>::iterator it = vecU.begin(); it != vecU.end(); it++)
	{
		vecGamma.push_back(Gamma(*it));		// add each price to the gamma vector
	}

	return vecGamma;				// return the gamma vector
}



// =========================================================================================================

// calculate call and put prices from each other using put-call parity relationship
double EuropeanOption::PCP_Price(double U) const
{
	if (optType == "C")
	{
		double P = CallPrice(U) + K * exp(-r * T) - U;		// calculate put price using PCP
		return P;
	}
	else
	{
		double C = PutPrice(U) - K * exp(-r * T) + U;		// calculate call price using PCP
		return C;
	}
}

// check if the PCP is satisfied
bool EuropeanOption::SatisfyPCP(double call_price, double put_price, double U) const
{
	if ((call_price + K * exp(-r * T)) == (put_price + U))	// the PCP is satisfied
	{
		cout << "Put-call parity is satisfied." << endl;
		return true;
	}
	else
	{
		cout << "Put-call parity is not satisfied." << endl;	// the PCP is not satisfied
		return false;
	}
}
