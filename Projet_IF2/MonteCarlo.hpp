//
//  MonteCarlo.hpp
//  Projet_IF2
//
//  Created by Arthur Cluet on 20/12/2022.
//

#ifndef MonteCarlo_hpp
#define MonteCarlo_hpp

#include <stdio.h>
#include <random>

class MonteCarloIntegralComputer {
    int n;
    std::mt19937 gen;
    double a;
    double b;
    double sum;
    double sum2;
    double e;
    double estimation;
    virtual double f(double x) = 0;
public:
    MonteCarloIntegralComputer(double a, double b, std::mt19937 * gen);
    void compute(int nb_points);
    //std::string operator()();
    double operator()();
};


#endif /* MonteCarlo_hpp */
