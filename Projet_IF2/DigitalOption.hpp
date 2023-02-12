//
//  DigitalOption.hpp
//  Projet_IF2
//
//  Created by Arthur Cluet on 20/12/2022.
//

#ifndef DigitalOption_hpp
#define DigitalOption_hpp

#include <stdio.h>
#include <iostream>
#include "Option.hpp"
#include "VanillaOption.hpp"

class DigitalOption : public VanillaOption {
protected:
    double _strike;
public:
    // Constructeur
    DigitalOption(double expiry, double strike) : VanillaOption(expiry, strike){
        if(expiry >= 0 && strike >= 0){
            _strike = strike;
        } else {
            std::cout << "Erreur paramètres (1)" << std::endl;
        }
    };
    
    friend class BlackScholesPricer;
};

class DigitalCallOption : public DigitalOption {
public:
    DigitalCallOption(double expiry, double strike) : DigitalOption(expiry, strike){};
    double payoff(double z){
        if(z >= _strike){
            return 1;
        } else {
            return 0;
        }
    }
    optionType GetOptionType(){
        return optionType::digitalCall;
    }
};

class DigitalPutOption : public DigitalOption {
public:
    DigitalPutOption(double expiry, double strike) : DigitalOption(expiry, strike){};
    double payoff(double z){
        if(_strike >= z){
            return 1;
        } else {
            return 0;
        }
    }
    optionType GetOptionType(){
        return optionType::digitalPut;
    }
};


#endif /* DigitalOption_hpp */
