#pragma once

#include "AsianOption.h"
#include <vector>

class AsianPutOption : public AsianOption {
protected:
	double _strike;
public:
	AsianPutOption(std::vector<double> ts, double strike) : AsianOption(ts), _strike(strike) {};
	double payoff(double z) {
		return (_strike - z > 0) ? _strike - z : 0;
	}
};
