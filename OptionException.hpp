// OptionException.hpp
// A exception class for options

// Prevent using pre-processor directives
#ifndef OPTIONEXCEPTION_HPP
#define OPTIONEXCEPTION_HPP

#include <iostream>
#include <string>
#include <sstream>

using namespace std;



// OptionException class: base class =====================================================================================

class OptionException
{
public:
	virtual string GetMessage() const = 0;		// An abstract GetMessage() function that returns a std::string
};



// OptionTypeException class: derived class =====================================================================================

class OptionTypeException : public OptionException
{
public:
	// Constructor
	OptionTypeException() : OptionException() {};	// default constructor
	virtual ~OptionTypeException() {};				// destructor

	virtual string GetMessage() const		// GetMessage function() in derived class
	{
		stringstream exp_sstream;
		exp_sstream << "!!! Unknown Option Type";

		return exp_sstream.str();
	};
};

// OptionClassException class: derived class =====================================================================================

class OptionClassException : public OptionException
{
public:
	// Constructor
	OptionClassException() : OptionException() {};	// default constructor
	virtual ~OptionClassException() {};				// destructor

	virtual string GetMessage() const		// GetMessage function() in derived class
	{
		stringstream exp_sstream;
		exp_sstream << "!!! Unknown Option Class";

		return exp_sstream.str();
	};
};


#endif