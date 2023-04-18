#pragma once

#include "Option.h"

class AsianOption : public Option
{
private:
	std::vector<double> _ts;
public:
	AsianOption(std::vector<double> ts) : Option(ts.back()), _ts(ts) {};
	std::vector<double> getTimeSteps() {
		return _ts;
	};
	double payoffPath(vector<double> St) override {
		double s = 0;
		for (int i = 0; i < St.size(); i++) {
			s += St[i];
		}
		s /= St.size();
		s = payoff(s);
		return s;
	};
	bool isAsianOption() override { return true; }
};
