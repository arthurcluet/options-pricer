#pragma once

#include "Option.h"

class AmericanOption : public Option
{
protected:
	double _strike;
public:
	AmericanOption(double expiry, double strike) : Option(expiry), _strike(strike) {};
	bool isAmericanOption() override { return true; }
};


