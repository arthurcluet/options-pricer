//
//  BlackScholesMCPricer.hpp
//  Projet_IF2
//
//  Created by Arthur Cluet on 20/12/2022.
//

#ifndef BlackScholesMCPricer_hpp
#define BlackScholesMCPricer_hpp

#include <stdio.h>
#include <math.h>
#include <vector>
#include "Option.hpp"
#include "AsianOption.hpp"
#include "MT.hpp"

class BlackScholesMCPricer {
private:
    Option* _option; // ts: [t1, ..., tm], _strike
    double _initial_price; // S0
    double _interest_rate; // r
    double _volatility; // vol
    int _nbPaths; // nb généré
    double _priceSum;
public:
    BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility) : _initial_price(initial_price), _interest_rate(interest_rate), _volatility(volatility), _nbPaths(0), _priceSum(0) {
        
        std::cout << &option << std::endl;
        
        if(option->isAsianOption()){
            AsianCallOption* p = dynamic_cast<AsianCallOption*>(option);
            std::cout << p->getTimeSteps().size() << std::endl;
        } else {
            std::cout << "not asian" << std::endl;
        }
        
    };
    int getNbPaths(){ return _nbPaths; }
//    void generate(int nb_paths){
//
//        for(int i = 0; i < (*_option).getTimeSteps().size(); i++){
//            std::cout << "h" << std::endl;
//        }
//
//        for(int i = 0; i < nb_paths; i++){
//            // On génère un path St:
//            // S0 est _initial_price
//            std::vector<double> St{};
//            for(int j = 0; j < _option->_ts.size(); j++){
//                if(j == 0){
//                    St.push_back(_initial_price * exp( (_interest_rate - _volatility*_volatility/2)*_option->_ts[j] + _volatility*sqrt(_option->_ts[j])*MT::rand_norm() ));
//                } else {
//                    St.push_back(St[j - 1] * exp(  (_interest_rate - _volatility*_volatility/2) * (_option->_ts[j] - _option->_ts[j-1]) + _volatility * sqrt(_option->_ts[j] - _option->_ts[j-1]) * MT::rand_norm()));
//                }
//            }
//
//            // On calcule h(St1, ..., Stm)
//            double h = _option->payoffPath(St);
//
//            _nbPaths++;
//            _priceSum += h;
//        }
//    }
    
//    double operator()(){
//        if(_nbPaths == 0){
//            throw std::invalid_argument("No estimation");
//        } else {
//            return exp(-_interest_rate*_option->_ts[_option->_ts.size()]) * _priceSum / _nbPaths;
//        }
//    }
};

#endif /* BlackScholesMCPricer_hpp */
