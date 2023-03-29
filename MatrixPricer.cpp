// MatrixPricer.cpp
// Matrix class for options


#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

#include "Option.hpp"
#include "EuropeanOption.hpp"
#include "PerpetualAmericanOption.hpp"
#include "MatrixPricer.hpp"
#include "OptionException.hpp"

using namespace std;

// Constructor
MatrixPricer::MatrixPricer(): m_num(0)
{
}

// Destructor
MatrixPricer::~MatrixPricer()
{
}



// Generate parameter matrix =========================================================================================================

// 1. from hardcode
void MatrixPricer::GenMatrix(vector<double> v_r, vector<double> v_sig, vector<double> v_K, vector<double> v_T, vector<double> v_b, vector<double> v_S, vector<double> v_optType, vector<double> v_optClass)
{
	// get the number of options
	m_num = v_r.size();
	// push in the parameter vectors
	m_para.clear();
	m_para.push_back(v_r);
	m_para.push_back(v_sig);
	m_para.push_back(v_K);
	m_para.push_back(v_T);
	m_para.push_back(v_b);
	m_para.push_back(v_S);
	m_para.push_back(v_optType);
	m_para.push_back(v_optClass);
}

// 2. from console
void MatrixPricer::GenMatrix()
{
	// get the number of options
	cout << "Input the number of options: ";
	cin >> m_num;

	// get parameter vector from user
	vector<double> v_r(m_num);
	cout << "Input the vector r (" << m_num << " numbers)";
	for (int i = 0; i < m_num; i++)
	{
		cin >> v_r[i];
	}

	vector<double> v_sig(m_num);
	cout << "Input the vector sig (" << m_num << " numbers)";
	for (int i = 0; i < m_num; i++)
	{
		cin >> v_sig[i];
	}

	vector<double> v_K(m_num);
	cout << "Input the vector K (" << m_num << " numbers)";
	for (int i = 0; i < m_num; i++)
	{
		cin >> v_K[i];
	}

	vector<double> v_T(m_num);
	cout << "Input the vector T (" << m_num << " numbers)";
	for (int i = 0; i < m_num; i++)
	{
		cin >> v_T[i];
	}

	vector<double> v_b(m_num);
	cout << "Input the vector b (" << m_num << " numbers)";
	for (int i = 0; i < m_num; i++)
	{
		cin >> v_b[i];
	}
	vector<double> v_S(m_num);
	cout << "Input the vector S (" << m_num << " numbers)";
	for (int i = 0; i < m_num; i++)
	{
		cin >> v_S[i];
	}

	vector<double> v_optType(m_num);
	cout << "Input the vector optType (" << m_num << " numbers)";
	for (int i = 0; i < m_num; i++)
	{
		cin >> v_optType[i];
	}

	vector<double> v_optClass(m_num);
	cout << "Input the vector optClass (" << m_num << " numbers)";
	for (int i = 0; i < m_num; i++)
	{
		cin >> v_optClass[i];
	}

	// push in the parameter vectors
	m_para.clear();
	m_para.push_back(v_r);
	m_para.push_back(v_sig);
	m_para.push_back(v_K);
	m_para.push_back(v_T);
	m_para.push_back(v_b);
	m_para.push_back(v_S);
	m_para.push_back(v_optType);
	m_para.push_back(v_optClass);

}


// 3. from random number
void MatrixPricer::GenMatrix(int opt_num)
{
	// get the number of options
	m_num = opt_num;

	// get parameter vector from random
	vector<double> v_r(m_num);
	srand(time(0));
	for (int i = 0; i < m_num; i++)
	{
		v_r[i] = (rand() % 10) * 0.01+0.01;
	}

	vector<double> v_sig(m_num);
	srand(time(0));
	for (int i = 0; i < m_num; i++)
	{
		v_sig[i] = (rand() % 10) * 0.1+0.1;
	}

	vector<double> v_K(m_num);
	srand(time(0));
	for (int i = 0; i < m_num; i++)
	{
		v_K[i] = rand() % 100 +5;
	}

	vector<double> v_T(m_num);
	srand(time(0));
	for (int i = 0; i < m_num; i++)
	{
		v_T[i] = int(rand() % 10) * 0.25 + 0.25;
	}

	vector<double> v_b(m_num);
	srand(time(0));
	for (int i = 0; i < m_num; i++)
	{
		v_b[i] = v_r[i];
	}

	vector<double> v_S(m_num);
	srand(time(0));
	for (int i = 0; i < m_num; i++)
	{
		v_S[i] = rand() % 100 + 10;
	}

	vector<double> v_optType(m_num);
	srand(time(0));
	for (int i = 0; i < m_num; i++)
	{
		if ((rand() % 10) < 5)
		{
			v_optType[i] = 0;
		}
		else
		{
			v_optType[i] = 1;
		}
	}

	vector<double> v_optClass(m_num);
	srand(time(0));
	for (int i = 0; i < m_num; i++)
	{
		if ((rand() % 10) < 5)
		{
			v_optClass[i] = 0;		// European option
		}
		else
		{
			v_optClass[i] = 1;		// Perpetual American option
		}
	}

	// push in the parameter vectors
	m_para.clear();
	m_para.push_back(v_r);
	m_para.push_back(v_sig);
	m_para.push_back(v_K);
	m_para.push_back(v_T);
	m_para.push_back(v_b);
	m_para.push_back(v_S);
	m_para.push_back(v_optType);
	m_para.push_back(v_optClass);
}


// 4. from mesh array
vector<double> Mesh_Array(double start, double end, double h);

void MatrixPricer::GenMatrix(int opt_num, double r_start, double r_step, double sig_start, double sig_step, double K_start, double K_step, double T_start, double T_step, double b_start, double b_step, double S_start, double S_step, vector<double> v_optType, vector<double> v_optClass)
{
	// get the number of options
	m_num = opt_num;

	// get parameter vector from mesh array
	vector<double> v_r = Mesh_Array(r_start, r_start + m_num * r_step, r_step);
	vector<double> v_sig = Mesh_Array(sig_start, sig_start + m_num * sig_step, sig_step);
	vector<double> v_K = Mesh_Array(K_start, K_start + m_num * K_step, K_step);
	vector<double> v_T = Mesh_Array(T_start, T_start + m_num * T_step, T_step);
	vector<double> v_b = Mesh_Array(b_start, b_start + m_num * b_step, b_step);
	vector<double> v_S = Mesh_Array(S_start, S_start + m_num * S_step, S_step);

	// push in the parameter vectors
	m_para.clear();
	m_para.push_back(v_r);
	m_para.push_back(v_sig);
	m_para.push_back(v_K);
	m_para.push_back(v_T);
	m_para.push_back(v_b);
	m_para.push_back(v_S);
	m_para.push_back(v_optType);
	m_para.push_back(v_optClass);
}



// Generate options from m_para =========================================================================================================

void MatrixPricer::GenOption()
{
	m_opt.clear();
	for (int i = 0; i < m_num; i++)
	{
		// change the double optType into string optType
		string optType;
		if (m_para[6][i] == 0)			// the option is call option
		{
			optType = "C";
		}
		else if (m_para[6][i] == 1)		// the option is put option
		{
			optType = "P";
		}
		else
		{
			throw OptionTypeException();	// if the option type is not 0 or 1, throw an exception
		}

		// push back option according to the option class
		if (m_para[7][i] == 0)
		{
			m_opt.push_back(new EuropeanOption(m_para[0][i], m_para[1][i], m_para[2][i], m_para[3][i], m_para[4][i], optType, string("Option")));
		}
		else if (m_para[7][i] == 1)
		{
			m_opt.push_back(new PerpetualAmericanOption(m_para[0][i], m_para[1][i], m_para[2][i], m_para[3][i], m_para[4][i], optType, string("Option")));
		}
		else
		{
			throw OptionClassException();	// if the option class is not 0 or 1, throw an exception
		}
	}
}


// Calculate functions =========================================================================================================

// Calculate price vector
vector<double> MatrixPricer::Price()
{
	GenOption();				// initialize the options from matrix
	vector<double> v_price;		// create a double vector to store the price

	for (int i = 0; i < m_num; i++)
	{
		v_price.push_back(m_opt[i]->Price(m_para[5][i]));		// calculate the price and push in the price
	}

	return v_price;
}

// Calculate delta vector
vector<double> MatrixPricer::Delta()
{
	GenOption();				// initialize the options from matrix
	vector<double> v_delta;		// create a double vector to store the delta

	for (int i = 0; i < m_num; i++)
	{
		v_delta.push_back(m_opt[i]->Delta(m_para[5][i]));		// calculate the delta and push in the delta
	}

	return v_delta;
}

// Calculate gamma vector
vector<double> MatrixPricer::Gamma()
{
	GenOption();				// initialize the options from matrix
	vector<double> v_gamma;		// create a double vector to store the gamma

	for (int i = 0; i < m_num; i++)
	{
		v_gamma.push_back(m_opt[i]->Gamma(m_para[5][i]));		// calculate the gamma and push in the gamma
	}

	return v_gamma;
}



// Print functions =================================================================================================================================

// Print the matrix
void MatrixPricer::PrintMatrix() const
{
	cout << "Parameter Matrix: " << endl;
	// print the header
	cout << setw(8) << "r" << setw(8) << "sig" << setw(8) << "K" << setw(8) << "T" << setw(8) << "b" << setw(8) << "S" << setw(10) << "OptType" << setw(10) << "OptClass" << endl;
	// print the data
	for (int i = 0; i < m_num; i++)
	{
		cout << setw(8) << m_para[0][i] << setw(8) << m_para[1][i] << setw(8) << m_para[2][i] << setw(8) << m_para[3][i] << setw(8) << m_para[4][i] << setw(8) << m_para[5][i] << setw(10) << m_para[6][i] << setw(10) << m_para[7][i] << endl;
	}

}
