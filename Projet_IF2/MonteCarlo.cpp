//
//  MonteCarlo.cpp
//  Projet_IF2
//
//  Created by Arthur Cluet on 20/12/2022.
//

#include "MonteCarlo.hpp"
#include <iostream>
#include <format>

MonteCarloIntegralComputer::MonteCarloIntegralComputer(double lbound, double ubound, std::mt19937 *generator){
    a = lbound;
    b = ubound;
    n = 0;
    sum = 0;
    sum2 = 0;
    estimation = 0;
    e = 0;
    gen = *generator;
}

void MonteCarloIntegralComputer::compute(int nb_points){
    std::uniform_real_distribution<> dis(a, b);
    for(int i = 0; i < nb_points; i++){
        double x = dis(gen);
        double y = f(x);
        sum += y;
        sum2 += y*y;
        n += 1;
    }
    if(n > 0){
        estimation = (b-a)*sum/(double)n;
        // e = c * sqrt(var / n)
        // c = 1.96 pour 95%
        // vr = 1/n(sum2) + (sum)/n ^2
        double variance = sum2/(double)n - (sum/(double)n)*(sum/(double)n);
        e = 1.96 * sqrt(variance / (double)n);
    }
}

//std::string MonteCarloIntegralComputer::operator()(){
//    return "" + std::to_string(estimation) + ", IC=[" + std::to_string(estimation-e) + "; " + std::to_string(estimation+e) +"]";
//}

double MonteCarloIntegralComputer::operator()(){
    return estimation;
}
