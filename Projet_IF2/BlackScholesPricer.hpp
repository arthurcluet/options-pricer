//
//  BlackScholesPricer.hpp
//  Projet_IF2
//
//  Created by Arthur Cluet on 18/11/2022.
//

#ifndef BlackScholesPricer_hpp
#define BlackScholesPricer_hpp

#include <stdio.h>
#include "VanillaOption.hpp"
#include "DigitalOption.hpp"

class BlackScholesPricer {
private:
    double _asset_price;
    double _interest_rate;
    double _volatility;
    VanillaOption* _option;
public:
    BlackScholesPricer(VanillaOption* option, double asset_price, double interest_rate, double volatility) : _option(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility) {};
    
    double operator()();
    double delta();
};



#endif /* BlackScholesPricer_hpp */
