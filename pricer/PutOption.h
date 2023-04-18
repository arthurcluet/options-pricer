#pragma once

#include "VanillaOption.h"


class PutOption : public VanillaOption
{
public:
    // Constructor
    PutOption(double expiry, double strike) : VanillaOption(expiry, strike) {};

    // payoff()
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

    optionType GetOptionType()
    {
        return optionType::put;
    }
};