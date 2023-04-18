#pragma once
#include "Option.h"
#include "AsianOption.h"
#include <vector>
#include "MT.h"
#include <thread>

class BlackScholesMCPricer
{
private:
    double _initial_price;
    double _interest_rate;
    double _volatility;
    Option* _option;
    int _nbPaths;
    double _sum;
    double _sumSquared;
    double _estimation;

public:
    BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility) : _option(option), _initial_price(initial_price), _interest_rate(interest_rate), _volatility(volatility), _nbPaths(0), _sum(0.0), _estimation(0.0), _sumSquared(0.0) {
        
            
    };
    int getNbPaths() { return _nbPaths; }
    void generate(int nb_paths) {
        if (nb_paths <= 0) return;

        if (_option->isAsianOption()) {
            // Asian option

            AsianOption* asianOption = dynamic_cast<AsianOption*>(_option);
            
            for (int i = 0; i < nb_paths; i++) {

                vector<double> z(asianOption->getTimeSteps().size());
                for (int j = 0; j < asianOption->getTimeSteps().size(); j++) {
                    z[j] = MT::rand_norm();
                }

                vector<double> St(asianOption->getTimeSteps().size());
                
                St[0] = (_initial_price * exp((_interest_rate - _volatility * _volatility / 2) * asianOption->getTimeSteps()[0] + _volatility * sqrt(asianOption->getTimeSteps()[0]) * z[0]));
                for (int j = 1; j < asianOption->getTimeSteps().size(); j++) {
                    St[j] = (St[j-1] * exp((_interest_rate - _volatility*_volatility/2)*(asianOption->getTimeSteps()[j] - asianOption->getTimeSteps()[j - 1]) + _volatility*sqrt(asianOption->getTimeSteps()[j] - asianOption->getTimeSteps()[j - 1])*z[j]));
                }
                // ici on a une séquence (St1, ..., Stm)
                // on ajoute h(St1, ... Stm) à _sum
                _nbPaths++;
                _sum += asianOption->payoffPath(St);
                _sumSquared += asianOption->payoffPath(St) * asianOption->payoffPath(St);
            }
        }
        else {
            // European option
            for (int i = 0; i < nb_paths; i++) {

                double z = MT::rand_norm();
                double St1 = _initial_price * exp( (_interest_rate - _volatility * _volatility /2) * _option->getExpiry() + _volatility * sqrt(_option->getExpiry()) * z );

                _nbPaths++;
                _sum += _option->payoff(St1);
                _sumSquared += _option->payoff(St1) * _option->payoff(St1);
            }

            
        }

        // Mise à jour de l'estimation

        _estimation = exp(-_interest_rate * _option->getExpiry()) * _sum / _nbPaths;

    }
    


    double operator()() {
        return _estimation;
    }

    vector<double> confidenceInterval() {
        //double variance = _sumSquared / (double)_nbPaths - (_sum / (double)_nbPaths) * (_sum / (double)_nbPaths);
        double strd = sqrt(_sumSquared / _nbPaths - (_sum / _nbPaths) * (_sum / _nbPaths));
        double e = 1.96 * strd / sqrt(_nbPaths);
        vector<double> interval(2);
        interval[0] = _estimation - e;
        interval[1] = _estimation + e;
        return interval;
    }
};

