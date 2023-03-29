// MatrixPricer.hpp
// Matrix class for options

#ifndef MATRIXPRICER_HPP
#define MATRIXPRICER_HPP

#include <vector>
#include <string>
#include "Option.hpp"

using namespace std;

class MatrixPricer
{
private:
	vector<vector<double>> m_para;	// matrix of parameter vectors
	vector<Option*> m_opt;
	int m_num;						// the number of options

public:
	// Constructor
	MatrixPricer();		// default constructor

	// Destructor
	~MatrixPricer();

	// Generate parameter matrix
	// 1. from hardcode
	void GenMatrix(vector<double> v_r, vector<double> v_sig, vector<double> v_K, vector<double> v_T, vector<double> v_b, vector<double> v_S, vector<double> v_optType, vector<double> v_optClass);
	// 2. from console
	void GenMatrix();
	// 3. from random number
	void GenMatrix(int opt_num);
	// 4. from mesh array
	void GenMatrix(int opt_num, double r_start, double r_step, double sig_start, double sig_step, double K_start, double K_step, double T_start, double T_step, double b_start, double b_step, double S_start, double S_step, vector<double> v_optType, vector<double> v_optClass);
	
	// Generate options
	void GenOption();

	vector<double> Price();	// calculate price vector
	vector<double> Delta();	// calculate delta vector
	vector<double> Gamma();	// calculate gamma vector

	// Print functions
	void PrintMatrix() const;
};


#endif // !MATRIXPRICER_HPP
