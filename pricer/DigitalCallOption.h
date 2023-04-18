#pragma once

#include "DigitalOption.h"


class DigitalCallOption : public DigitalOption
{
public:
    DigitalCallOption(double expiry, double strike) : DigitalOption(expiry, strike) {};
    double payoff(double z) {
        if (z >= _strike) {
            return 1;
        }
        else {
            return 0;
        }
    }
    optionType GetOptionType()
    {
        return optionType::call;
    }
};
