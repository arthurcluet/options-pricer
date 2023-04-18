#pragma once

#include "Option.h"
#include "VanillaOption.h"
#include "DigitalOption.h"
#include "MT.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

using namespace std;

class BlackScholesPricer
{
private:
    double _asset_price;
    double _interest_rate;
    double _volatility;
    VanillaOption* _option;
    DigitalOption* _optionDigitale;
    double normalCDF(double x)
    {
        return (1 + erf(x / M_SQRT2)) / 2;
    }
    double NormalDF(double x)
    {
        return exp(-x * x / 2) / sqrt(2 * M_PI);
    }
public:
    BlackScholesPricer(VanillaOption* option, double asset_price, double interest_rate, double volatility) : _option(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility) {};
    BlackScholesPricer(DigitalOption* option, double asset_price, double interest_rate, double volatility) : _optionDigitale(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility) {};
    
    double operator()() {
        std::mt19937& mt = MT::Gen();
        double price;

        if (_option) {
            double d1 = (log(_asset_price / _option->_strike) + _option->_expiry * (_interest_rate + (_volatility * _volatility / 2))) / (_volatility * sqrt(_option->_expiry));
            double d2 = d1 - _volatility * sqrt(_option->_expiry);
            double Nd1 = normalCDF(d1);
            double Nd2 = normalCDF(d2);
            double Nd1M = (1 - Nd1);
            double Nd2M = (1 - Nd2);
            if (_option->GetOptionType() == VanillaOption::optionType::call)
            {
                // Call vanille
                price = _asset_price * Nd1 - _option->_strike * exp(-_interest_rate * (_option->_expiry)) * Nd2;
            }
            else
            {
                // Put vanille
                price = _option->_strike * exp(-_interest_rate * (_option->_expiry)) * Nd2M - _asset_price * Nd1M;
            }
        }
        else {
            double d1 = (log(_asset_price / _optionDigitale->_strike) + _optionDigitale->_expiry * (_interest_rate + (_volatility * _volatility / 2))) / (_volatility * sqrt(_optionDigitale->_expiry));
            double d2 = d1 - _volatility * sqrt(_optionDigitale->_expiry);
            double Nd1 = normalCDF(d1);
            double Nd2 = normalCDF(d2);
            double Nd1M = (1 - Nd1);
            double Nd2M = (1 - Nd2);
            if (_optionDigitale->GetOptionType() == DigitalOption::optionType::call) {
                // Digital Call
                price = exp(_interest_rate * _optionDigitale->_expiry) * Nd2;
            }
            else {
                // Digital Put
                price = exp(_interest_rate * _optionDigitale->_expiry) * Nd2M;
            }
        }

        return price;
    };

    double delta() {
        std::mt19937& mt = MT::Gen();

        double delta;
        if (_option) {
            double d1 = (log(_asset_price / _option->_strike) + _option->_expiry * (_interest_rate + (_volatility * _volatility / 2))) / (_volatility * sqrt(_option->_expiry));
            double d2 = d1 - _volatility * sqrt(_option->_expiry);
            double Nd1 = normalCDF(d1);
            if (_option->GetOptionType() == VanillaOption::optionType::call)
            {
                // Call vanille
                delta = Nd1;
            }
            else
            {
                // Put vanille
                delta = -exp(_interest_rate * _option->_expiry) * NormalDF(d2) / (_volatility * _asset_price * sqrt(_option->_expiry));
            }
        }
        else {
            double d1 = (log(_asset_price / _optionDigitale->_strike) + _optionDigitale->_expiry * (_interest_rate + (_volatility * _volatility / 2))) / (_volatility * sqrt(_optionDigitale->_expiry));
            double d2 = d1 - _volatility * sqrt(_optionDigitale->_expiry);
            double Nd1 = normalCDF(d1);
            // Call digital
            if (_optionDigitale->GetOptionType() == DigitalOption::optionType::call) {
                delta = exp(_interest_rate * _optionDigitale->_expiry) * NormalDF(d2) / (_volatility * _asset_price * sqrt(_optionDigitale->_expiry));
            }
            // Put digital
            else {
                delta = -exp(_interest_rate * _optionDigitale->_expiry) * NormalDF(d2) / (_volatility * _asset_price * sqrt(_optionDigitale->_expiry));
            }
        }

        return delta;
    };
};
