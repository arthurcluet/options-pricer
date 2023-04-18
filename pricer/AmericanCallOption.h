#pragma once

#include "AmericanOption.h"

class AmericanCallOption : public AmericanOption {
public:
    AmericanCallOption(double expiry, double strike) : AmericanOption(expiry, strike) {};
    double payoff(double z) override
    {
        if (z >= _strike)
        {
            return z - _strike;
        }
        else
        {
            return 0;
        }
    }
};