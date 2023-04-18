#pragma once

#include "AsianOption.h"


class AsianCallOption : public AsianOption {
protected:
	double _strike;
public:
	AsianCallOption(std::vector<double> ts, double strike) : AsianOption(ts), _strike(strike) {};
	double payoff(double z) {
		return (z - _strike > 0) ? z - _strike : 0;
	}
};
