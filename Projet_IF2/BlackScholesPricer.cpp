//
//  BlackScholesPricer.cpp
//  Projet_IF2
//
//  Created by Arthur Cluet on 18/11/2022.
//

#include "BlackScholesPricer.hpp"
#include "MonteCarlo.hpp"
#include "MT.hpp"
#include <math.h>

// Standard Normal Cumulative Distribution Function
class standardNormalCDF : public MonteCarloIntegralComputer{
    double f(double x){
        return (exp(-x*x/2))/(sqrt(2*M_PI));
    }
public:
    standardNormalCDF(double a, double b, std::mt19937 * generator) : MonteCarloIntegralComputer(a, b, generator) {
        //gen = *generator;
    };
};

double normalCDF(double x){
    return (1+erf(x / M_SQRT2))/2;
}

double NormalDF(double x){
    return exp(-x*x/2)/sqrt(2*M_PI);
}

double BlackScholesPricer::operator()(){
    
    std::mt19937 &mt = MT::Gen();
    
    // d1 = ( ln(SP/ST) + (r - d + (σ2/2)) t ) / σ √t
    // d2 = d1 - σ √t
    
    double d1 = (log(_asset_price/_option->_strike) + _option->_expiry*(_interest_rate + (_volatility*_volatility/2))) / (_volatility*sqrt(_option->_expiry));
    double d2 = d1 - _volatility * sqrt(_option->_expiry);
    
    // Calcul de Nd1 et Nd2 avec Monte Carlo :
    
    //standardNormalCDF Nd1 = standardNormalCDF(-50, d1, &mt);
    //standardNormalCDF Nd2 = standardNormalCDF(-50, d2, &mt);
    //Nd1.compute(1000000);
    //Nd2.compute(1000000);
    
    double Nd1 = normalCDF(d1);
    double Nd2 = normalCDF(d2);
    double Nd1M = (1 - Nd1);
    double Nd2M = (1- Nd2);
    
    // C = SP e-dt N(d1) - ST e-rt N(d2)
    //P = ST e-rt N(-d2) - SP e-dt N(-d1)
    
    double price;

    if(_option->GetOptionType() == VanillaOption::optionType::call){
        // Call
        price = _asset_price * Nd1 - _option->_strike * exp(-_interest_rate*(_option->_expiry)) * Nd2;
    } else if(_option->GetOptionType() == VanillaOption::optionType::put) {
        // Put
        price = _option->_strike * exp(-_interest_rate*(_option->_expiry)) * Nd2M - _asset_price * Nd1M;
    } else if(_option->GetOptionType() == VanillaOption::optionType::digitalCall) {
        // Digital Call
        price = exp(_interest_rate*_option->_expiry)*Nd2;
    } else {
        // Digital Put
        price = exp(_interest_rate*_option->_expiry)*Nd2M;
    }

    return price;
}

double BlackScholesPricer::delta(){
    
    std::mt19937 &mt = MT::Gen();
    
    double d1 = (log(_asset_price/_option->_strike) + _option->_expiry*(_interest_rate + (_volatility*_volatility/2))) / (_volatility*sqrt(_option->_expiry));
    double d2 = d1 - _volatility * sqrt(_option->_expiry);
    
    double Nd1 = normalCDF(d1);
    //standardNormalCDF Nd1 = standardNormalCDF(-50, d1, &mt);
    //Nd1.compute(1000000);
    
    double delta;
    if(_option->GetOptionType() == VanillaOption::optionType::call){
        // Call
        delta = Nd1;
    } else if(_option->GetOptionType() == VanillaOption::optionType::put) {
        // Put
        delta = Nd1 - 1;
    }else if(_option->GetOptionType() == VanillaOption::optionType::digitalCall) {
        delta = exp(_interest_rate*_option->_expiry)*NormalDF(d2)/(_volatility*_asset_price*sqrt(_option->_expiry));
    }else {
        delta = -exp(_interest_rate*_option->_expiry)*NormalDF(d2)/(_volatility*_asset_price*sqrt(_option->_expiry));
    }
    
    return delta;
}
