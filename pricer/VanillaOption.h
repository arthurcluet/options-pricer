#pragma once

#include "Option.h"
#include <stdio.h>
#include <stdexcept>

using namespace std;

class VanillaOption : public Option

{
protected:
    double _strike;

public:
    enum class optionType
    {
        call,
        put
    };

    VanillaOption(double expiry, double strike) : Option(expiry)
    {
        if (expiry >= 0 && strike >= 0)
        {
            _strike = strike;
        }
        else
        {
            throw invalid_argument("Strike and Expiry can't be negative");
        }
    };

    virtual optionType GetOptionType() = 0;

    friend class BlackScholesPricer;
};

