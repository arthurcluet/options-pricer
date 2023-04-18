#pragma once

#include "VanillaOption.h"

class CallOption : public VanillaOption
{
public:
    CallOption(double expiry, double strike) : VanillaOption(expiry, strike) {};
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
    optionType GetOptionType()
    {
        return optionType::call;
    }
};
