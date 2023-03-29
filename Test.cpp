// Test.cpp
// This program is the test program of Group A and B

#include<string>
#include<iostream>
#include<vector>

#include"EuropeanOption.hpp"
#include"PerpetualAmericanOption.hpp"
#include"MatrixPricer.hpp"
#include"OptionException.hpp"

using namespace std;



// A1(a) test function
void A1a_OptionPricing(double r, double sig, double K, double T, double b, double S, string unam)
{
	EuropeanOption opt(r, sig, K, T, b, "C", unam);		// initialize the european option

	double call_price = opt.Price(S);	// calculate the call price using BS formula
	opt.toggle();						// change the optType to put
	double put_price = opt.Price(S);	// calculate the put price using BS formula

	cout << unam << ": C = " << call_price << ", P = " << put_price << ";" << endl;	// print result
}


// A1(b) test function
void A1b_OptionPricing(double r, double sig, double K, double T, double b, double S, string unam)
{
	// Calculate put price using call price
	EuropeanOption opt1(r, sig, K, T, b, "C", unam);		// initialize the european call option

	double call_price = opt1.Price(S);					// calculate the call price using BS formula
	double put_price = opt1.PCP_Price(S);				// calculate the put price from PCP

	cout << unam << ": C = " << call_price << ", P = " << put_price << "(using call price to calculate put price);" << endl;	// print result
	
	// Check if PCP is satisfied
	opt1.SatisfyPCP(call_price, put_price, S);


	// Calculate call price using put price
	EuropeanOption opt2(r, sig, K, T, b, "P", unam);		// initialize the european put option

	put_price = opt2.Price(S);					// calculate the put price using BS formula
	call_price = opt2.PCP_Price(S);				// calculate the call price from PCP

	cout << unam << ": C = " << call_price << ", P = " << put_price << "(using put price to calculate call price);" << endl;	// print result

	// Check if PCP is satisfied
	opt1.SatisfyPCP(call_price, put_price, S);
	cout << endl;
}


// mesh array global function: create a mesh array
vector<double> Mesh_Array(double start, double end, double h)
{
	vector<double> mesh_arr;	// create a mesh array
	for (double i = start; i < end; i = i + h)
	{
		mesh_arr.push_back(i);	// push back each element
	}

	return mesh_arr;
}


int main()
{
	// ================================A1(a)=================================================
	// Calculate call and put option price for Batch 1 to 4 using BS formula.
	cout << "=========================== A1(a) ===================================" << endl;
	
	double S = 108;
	double K = 120;
	double r = 0.045;
	double T = 1.45;
	double sig = 0.51;
	double b = 0;

	// double r_val, double sig_val, double K_val, double T_val, double b_val, string optType_val, string unam_val)
	EuropeanOption opt(r, sig, K, T, b, "P", "Batch 1");
	double price = opt.Price(S);
	double delta = opt.Delta(S);
	double gamma = opt.Gamma(S);
	cout << "price: " << price << endl;
	cout << "delta: " << delta << endl;
	cout << "gamma: " << gamma << endl;

	/*
	A1a_OptionPricing(0.00, 0.20, 100, 1.0, 0.0, 100, "Batch 2");
	A1a_OptionPricing(0.12, 0.50, 10, 1.0, 0.12, 5, "Batch 3");
	A1a_OptionPricing(0.08, 0.30, 100.0, 30.0, 0.08, 100.0, "Batch 4");
	*/


	/*
	// ================================A1(b)=================================================
	// Calculate call and put option price from each other and check if PCP is satisfied.
	cout << endl << endl << "=========================== A1(b) ===================================" << endl;
	
	A1b_OptionPricing(0.08, 0.30, 65, 0.25, 0.08, 60, "Batch 1");
	A1b_OptionPricing(0.00, 0.20, 100, 1.0, 0.0, 100, "Batch 2");
	A1b_OptionPricing(0.12, 0.50, 10, 1.0, 0.12, 5, "Batch 3");
	A1b_OptionPricing(0.08, 0.30, 100.0, 30.0, 0.08, 100.0, "Batch 4");




	// ================================A1(c)=================================================
	// Calculate prices for a increasing range of values of S
	cout << endl << endl << "=========================== A1(c) ===================================" << endl;
	
	EuropeanOption opt_A1c(0.08, 0.30, 65, 0.25, 0.08, "C", "A1(c)");		// initialize a call option
	vector<double> vecS_A1c = Mesh_Array(50, 70, 2);						// create a mesh array for S
	vector<double> vecC_A1c = opt_A1c.Price(vecS_A1c);				// calculate call price vector
	opt_A1c.toggle();												// change the call option to put option
	vector<double> vecP_A1c = opt_A1c.Price(vecS_A1c);				// calculate put price vector
	// print result
	for (int i = 0; i < vecS_A1c.size(); i++)
	{
		cout << "S = " << vecS_A1c[i] << ": C = " << vecC_A1c[i] << ", P = " << vecP_A1c[i] << ";" << endl;
	}




	// ================================A1(d)=================================================
	// Input a matrix (vector of vectors) of option parameters and receive a matrix of option prices as the result.
	cout << endl << endl << "=========================== A1(d) ===================================" << endl;

	// 1. from hardcode
	cout << "1. generate matrix from hardcode" << endl << endl;
	vector<double> v_r = { 0.08, 0, 0.12 };
	vector<double> v_sig = { 0.3, 0.2, 0.5};
	vector<double> v_K = { 65, 100, 10 };
	vector<double> v_T = { 0.25, 1.0, 1.0 };
	vector<double> v_b = { 0.08, 0, 0.12 };
	vector<double> v_S = { 60, 100, 5 };
	vector<double> v_optType = { 0, 0, 1 };		// 0: Call, 1: Put
	vector<double> v_optClass = { 0, 0, 0 };	// 0: European, 1: Perpetual American

	MatrixPricer pricer1;
	pricer1.GenMatrix(v_r, v_sig, v_K, v_T, v_b, v_S, v_optType, v_optClass);	// create a matrix
	pricer1.PrintMatrix();														// print the matrix
	
	vector<double> v_price1 = pricer1.Price();	// calculate the price

	cout << "The result:" << endl;
	for (int i = 0; i < v_price1.size(); i++)
	{
		cout << "Price: " << v_price1[i]  << ";" << endl;
	}
	cout << "---------------------------------------------------------------------" << endl;


	// 2. from console
	cout << endl << "2. generate matrix from console" << endl << endl;

	MatrixPricer pricer2;
	pricer2.GenMatrix();				// create a matrix, get data from keyboard
	pricer2.PrintMatrix();				// print the matrix

	vector<double> v_price2 = pricer2.Price();	// calculate the price

	cout << "The result:" << endl;
	for (int i = 0; i < v_price2.size(); i++)
	{
		cout << "Price: " << v_price2[i] << ";" << endl;
	}
	cout << "---------------------------------------------------------------------" << endl;


	// 3. from random number
	cout << endl << "3. generate matrix from random number" << endl << endl;

	MatrixPricer pricer3;
	pricer3.GenMatrix(3);				// create a matrix, random data
	pricer3.PrintMatrix();				// print the matrix

	vector<double> v_price3 = pricer3.Price();	// calculate the price

	cout << "The result:" << endl;
	for (int i = 0; i < v_price3.size(); i++)
	{
		cout << "Price: " << v_price3[i] << ";" << endl;
	}
	cout << "---------------------------------------------------------------------" << endl;


	// 4. from mesh array
	cout << endl << "4. generate matrix from mesh array" << endl << endl;

	MatrixPricer pricer4;
	pricer4.GenMatrix(3, 0.0, 0.02, 0.2, 0.1, 20, 40, 0.25, 0.25, 0.0, 0.02, 60, 10,v_optType, v_optClass);				// create a matrix, mesh array
	pricer4.PrintMatrix();						// print the matrix

	vector<double> v_price4 = pricer4.Price();	// calculate the price

	cout << "The result:" << endl;
	for (int i = 0; i < v_price4.size(); i++)
	{
		cout << "Price: " << v_price4[i] << ";" << endl;
	}
	cout << "---------------------------------------------------------------------" << endl;



	// 5. try exception - Option Type Exception
	try
	{
		cout << endl << "5. try exception - Option Type Exception" << endl << endl;
		vector<double> v_optType_exp = { 0, 0, 2 };				// create a optType not 1 or 0
		

		MatrixPricer pricer_exp1;
		pricer_exp1.GenMatrix(v_r, v_sig, v_K, v_T, v_b, v_S, v_optType_exp, v_optClass);	// create a matrix
		vector<double> v_price_exp1 = pricer_exp1.Price();		// calculate the price
	}
	catch (OptionException& err)
	{
		cout << err.GetMessage() << endl;
	}
	cout << "---------------------------------------------------------------------" << endl;


	// 6. try exception - Option Class Exception
	try
	{
		cout << endl << "6. try exception - Option Class Exception" << endl << endl;
		vector<double> v_optClass_exp = { 0, 2, 0 };		// create a optClass not 1 or 0

		MatrixPricer pricer_exp2;
		pricer_exp2.GenMatrix(v_r, v_sig, v_K, v_T, v_b, v_S, v_optType, v_optClass_exp);	// create a matrix
		vector<double> v_price_exp2 = pricer_exp2.Price();		// calculate the price
	}
	catch (OptionException& err)
	{
		cout << err.GetMessage() << endl;
	}





	// ================================A2(a)=================================================
	// Calculate delta and gamma for call and put future option pricing using the data set
	cout << endl << endl << "=========================== A2(a) ===================================" << endl;

	EuropeanOption opt_A2a(0.1, 0.36, 100, 0.5, 0, "C", "A2a");

	double call_delta = opt_A2a.Delta(105);		// calculate call delta
	double call_gamma = opt_A2a.Gamma(105);		// calculate call gamma

	opt_A2a.toggle();							// change call into put
	double put_delta = opt_A2a.Delta(105);		// calculate put delta
	double put_gamma = opt_A2a.Gamma(105);		// calculate put gamma

	cout << "delta call = " << call_delta << ", delta put = " << put_delta << endl;
	cout << "gamma call = " << call_gamma << ", gamma put = " << put_gamma << endl;





	// ================================A2(b)=================================================
	// Calculate delta and gamma for call and put future option pricing using mesh array
	cout << endl << endl << "=========================== A2(b) ===================================" << endl;

	EuropeanOption opt_A2b(0.1, 0.36, 100, 0.5, 0, "C", "A2b");

	vector<double> vS_A2b = Mesh_Array(105, 165, 20);		// create a mesh array for S
	vector<double> vCallDelta_A2b = opt_A2b.Delta(vS_A2b);	// calculate the call delta vector
	opt_A2b.toggle();
	vector<double> vPutDelta_A2b = opt_A2b.Delta(vS_A2b);	// calculate the put delta vector
	// print result
	for (int i = 0; i < vS_A2b.size(); i++)
	{
		cout << "S = " << vS_A2b[i] << ": delta call = " << vCallDelta_A2b[i] << ", delta put = " << vPutDelta_A2b[i] << ";" << endl;
	}




	// ================================A2(c)=================================================
	// Delta and Gamma function in matrix class
	cout << endl << endl << "=========================== A2(c) ===================================" << endl;

	pricer1.PrintMatrix();						// print the matrix

	vector<double> v_delta1 = pricer1.Delta();	// calculate the delta
	vector<double> v_gamma1 = pricer1.Gamma();	// calculate the gamma

	cout << "The result:" << endl;
	for (int i = 0; i < v_price1.size(); i++)
	{
		cout << "Delta: " << v_delta1[i] << ", Gamma: " << v_gamma1[i] << ";" << endl;
	}
	

	// ================================A2(d)=================================================
	// Numerical delta and Gamma function in matrix class
	cout << endl << endl << "=========================== A2(d) ===================================" << endl;

	EuropeanOption opt_A2d(0.1, 0.36, 100, 0.5, 0, "C", "A2d");

	double delta_actual = opt_A2d.Delta(105);		// calculate call delta
	double delta_h1 = opt_A2d.Delta(105, 1);		// calculate numerical delta, h = 1
	double delta_h2 = opt_A2d.Delta(105, 2);		// calculate numerical delta, h = 2
	double delta_h3 = opt_A2d.Delta(105, 3);		// calculate numerical delta, h = 3
	// print:
	cout << "Actual Delta = " << delta_actual << endl;
	cout << "h = 1, Numerical Delta = " << delta_h1 << endl;
	cout << "h = 2, Numerical Delta = " << delta_h2 << endl;
	cout << "h = 3, Numerical Delta = " << delta_h3 << endl << endl;


	double gamma_actual = opt_A2d.Gamma(105);		// calculate call gamma
	double gamma_h1 = opt_A2d.Gamma(105, 1);		// calculate numerical gamma, h = 1
	double gamma_h2 = opt_A2d.Gamma(105, 2);		// calculate numerical gamma, h = 2
	double gamma_h3 = opt_A2d.Gamma(105, 3);		// calculate numerical gamma, h = 3
	// print:
	cout << "Actual Gamma = " << gamma_actual << endl;
	cout << "h = 1, Numerical Gamma = " << gamma_h1 << endl;
	cout << "h = 2, Numerical Gamma = " << gamma_h2 << endl;
	cout << "h = 3, Numerical Gamma = " << gamma_h3 << endl;

	// result: the smaller h is, the numerical result closer to actual result


	// ================================B(b)=================================================
	// Test with the given data
	cout << endl << endl << "=========================== B(b) ===================================" << endl;

	PerpetualAmericanOption opt_Bb(0.1, 0.1, 100, 1, 0.02, "C", "Bb");

	double call_price = opt_Bb.Price(110);		// calculate call price
	opt_Bb.toggle();							// change call into put
	double put_price = opt_Bb.Price(110);		// calculate put price

	cout << "C = " << call_price << ", P = " << put_price << endl;




	// ================================B(c)=================================================
	// Calculate delta and gamma for call and put future option pricing using mesh array
	cout << endl << endl << "=========================== B(c) ===================================" << endl;

	PerpetualAmericanOption opt_Bc(0.1, 0.1, 100, 1, 0.02, "C", "Bc");

	vector<double> vS_Bc = Mesh_Array(110, 170, 20);		// create a mesh array for S
	vector<double> vC_Bc = opt_Bc.Price(vS_Bc);				// calculate the call delta vector
	opt_Bc.toggle();
	vector<double> vP_Bc = opt_Bc.Price(vS_Bc);				// calculate the put delta vector
	// print result
	for (int i = 0; i < vS_Bc.size(); i++)
	{
		cout << "S = " << vS_Bc[i] << ": C = " << vC_Bc[i] << ", P = " << vP_Bc[i] << ";" << endl;
	}





	// ================================B(d)=================================================
	// Calculate delta and gamma for call and put future option pricing using mesh array
	cout << endl << endl << "=========================== B(d) ===================================" << endl;

	// 1. from hardcode
	cout << "1. generate matrix from hardcode" << endl << endl;
	v_r = { 0.1, 0.1, 0.12 };
	v_sig = { 0.1, 0.1, 0.2 };
	v_K = { 100, 100, 50 };
	v_T = { 1.0, 1.0, 1.0 };
	v_b = { 0.02, 0.02, 0.10 };
	v_S = { 110, 110, 80 };
	v_optType = { 0, 1, 0 };		// 0: Call, 1: Put
	v_optClass = { 1, 1, 1 };		// 0: European, 1: Perpetual American

	pricer1.GenMatrix(v_r, v_sig, v_K, v_T, v_b, v_S, v_optType, v_optClass);	// create a matrix
	pricer1.PrintMatrix();														// print the matrix

	v_price1 = pricer1.Price();		// calculate the price

	cout << "The result:" << endl;
	for (int i = 0; i < v_price1.size(); i++)
	{
		cout << "Price: " << v_price1[i] << ";" << endl;
	}
	cout << "---------------------------------------------------------------------" << endl;


	// 2. from console
	cout << endl << "2. generate matrix from console" << endl << endl;

	pricer2.GenMatrix();				// create a matrix, get data from keyboard
	pricer2.PrintMatrix();				// print the matrix

	v_price2 = pricer2.Price();			// calculate the price

	cout << "The result:" << endl;
	for (int i = 0; i < v_price2.size(); i++)
	{
		cout << "Price: " << v_price2[i] << ";" << endl;
	}
	cout << "---------------------------------------------------------------------" << endl;


	// 3. from random number
	cout << endl << "3. generate matrix from random number" << endl << endl;

	pricer3.GenMatrix(3);				// create a matrix, random data
	pricer3.PrintMatrix();				// print the matrix

	v_price3 = pricer3.Price();			// calculate the price

	cout << "The result:" << endl;
	for (int i = 0; i < v_price3.size(); i++)
	{
		cout << "Price: " << v_price3[i] << ";" << endl;
	}
	cout << "---------------------------------------------------------------------" << endl;


	// 4. from mesh array
	cout << endl << "4. generate matrix from mesh array" << endl << endl;

	pricer4.GenMatrix(3, 0.1, 0.01, 0.1, 0.01, 100, 10, 0.25, 0.25, 0.02, 0.01, 110, 20, v_optType, v_optClass);				// create a matrix, mesh array
	pricer4.PrintMatrix();						// print the matrix

	v_price4 = pricer4.Price();					// calculate the price

	cout << "The result:" << endl;
	for (int i = 0; i < v_price4.size(); i++)
	{
		cout << "Price: " << v_price4[i] << ";" << endl;
	}
	cout << "---------------------------------------------------------------------" << endl;

	*/
}

	


