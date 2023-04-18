#pragma once

#include "AmericanOption.h"

class AmericanPutOption : public AmericanOption {
public:
    AmericanPutOption(double expiry, double strike) : AmericanOption(expiry, strike) {};

    double payoff(double z) override
    {
        if (_strike >= z)
        {
            return _strike - z;
        }
        else
        {
            return 0;
        }
    }
};