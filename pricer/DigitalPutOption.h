#pragma once

#include "DigitalOption.h"


class DigitalPutOption : public DigitalOption
{
public:
    // Constructor
    DigitalPutOption(double expiry, double strike) : DigitalOption(expiry, strike) {};

    double payoff(double z) {
        if (_strike >= z) {
            return 1;
        }
        else {
            return 0;
        }
    }

    optionType GetOptionType()
    {
        return optionType::put;
    }
};