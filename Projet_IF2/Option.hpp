//
//  Option.hpp
//  Projet_IF2
//
//  Created by Arthur Cluet on 18/11/2022.
//

#ifndef Option_hpp
#define Option_hpp

#include <stdio.h>
#include <vector>

class Option{
private:
    double _expiry;
public:
    Option(double expiry) : _expiry(expiry) {};
    virtual double payoff(double) = 0;
    
    double payoffPath(double);
    bool isAsianOption();
    
    friend class BlackScholesPricer;
    friend class CRRPricer;
    friend class BlackScholesMCPricer;
};


#endif /* Option_hpp */
