//
//  VanillaOption.hpp
//  Projet_IF2
//
//  Created by Arthur Cluet on 18/11/2022.
//

#ifndef VanillaOption_hpp
#define VanillaOption_hpp

#include <stdio.h>
#include <iostream>
#include "Option.hpp"

class VanillaOption : public Option {
protected:
    double _strike;
public:
    // optionType enum
    enum class optionType{ call, put, digitalCall, digitalPut };
    // Constructeur
    VanillaOption(double expiry, double strike) : Option(expiry){
        if(expiry >= 0 && strike >= 0){
            _strike = strike;
        } else {
            throw std::invalid_argument("Strike and Expiry can't be negative");
        }
    };
    // GetOptionType()
    virtual optionType GetOptionType() = 0;
    
    friend class BlackScholesPricer;
};

class CallOption : public VanillaOption {
public:
    CallOption(double expiry, double strike) : VanillaOption(expiry, strike){};
    double payoff(double z){
        if(z >= _strike){
            return z - _strike;
        } else {
            return 0;
        }
    }
    optionType GetOptionType(){
        return optionType::call;
    }
};

class PutOption : public VanillaOption {
public:
    PutOption(double expiry, double strike) : VanillaOption(expiry, strike){};
    double payoff(double z){
        if(_strike >= z){
            return _strike - z;
        } else {
            return 0;
        }
    }
    optionType GetOptionType(){
        return optionType::put;
    }
};


#endif /* VanillaOption_hpp */
