//
//  AsianOption.hpp
//  Projet_IF2
//
//  Created by Arthur Cluet on 20/12/2022.
//

#ifndef AsianOption_hpp
#define AsianOption_hpp

#include <stdio.h>
#include <vector>
#include "Option.hpp"

class AsianOption : public Option {
private:
    std::vector<double> _ts;
public:
    AsianOption(std::vector<double> ts) : Option(0), _ts(ts) {};
    std::vector<double> getTimeSteps(){
        return _ts;
    }
    double payoffPath(std::vector<double> St){
        double s = 0;
        for(int i = 0; i < St.size(); i++){
            s += St[i];
        }
        s /= St.size();
        s = payoff(s);
        return s;
    }
    
    bool isAsianOption(){
        return true;
    }
    // inutilisé
    double payoff(double x){
        return 0;
    }
};

class AsianCallOption : public AsianOption {
private:
    double _strike;
public:
    AsianCallOption(std::vector<double> ts, double strike) : AsianOption(ts), _strike(strike) {};
    double payoff(std::vector<double> St){
        // C(T) = max(A(0, T) - K, 0)  A is average
        double A = payoffPath(St);
        return (A - _strike > 0) ? A - _strike : 0;
    }
};

class AsianPutOption : public AsianOption {
private:
    double _strike;
public:
    AsianPutOption(std::vector<double> ts, double strike) : AsianOption(ts), _strike(strike) {};
    double payoff(std::vector<double> St){
        // P(T) = max(K - A(O, T)), 0)
        double A = payoffPath(St);
        return (_strike - A > 0) ? _strike - A : 0;
    }
};

#endif /* AsianOption_hpp */
