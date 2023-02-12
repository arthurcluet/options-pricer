//
//  main.cpp
//  Projet_IF2
//
//  Created by Arthur Cluet on 18/11/2022.
//

#include <iostream>
#include <random>
#include <math.h>

#include "VanillaOption.hpp"
#include "MT.hpp"
#include "BlackScholesPricer.hpp"
#include "MonteCarlo.hpp"
#include "CRRPricer.hpp"
#include "AsianOption.hpp"
#include "BlackScholesMCPricer.hpp"

using namespace std;


int main(int argc, const char * argv[]) {
    
    // Générateur unique pour toute l'execution
    //std::mt19937 &mt = Random::Gen();
    
    // Création des options (Call / Put / Digital Call / Digital Put)
    double interestRate = 0.01;
    double vol = 0.1;
    double assetPrice = 100;
    CallOption call(5, 101);
    PutOption put(5, 101);
    DigitalCallOption dcall(5, 101);
    DigitalPutOption dput(5, 101);
    
    // Black Scholes Pricer
    BlackScholesPricer callPricer(&call, assetPrice, interestRate, vol);
    BlackScholesPricer putPricer(&put, assetPrice, interestRate, vol);
    BlackScholesPricer digitalCallPricer(&dcall, assetPrice, interestRate, vol);
    BlackScholesPricer digitalPutPricer(&dput, assetPrice, interestRate, vol);
    std::cout << "*** Black Scholes ***" << std::endl;
    std::cout << "Call: $" << callPricer() << ", Delta: " << callPricer.delta() << std::endl;
    std::cout << "Put: $" << putPricer() << ", Delta: " << putPricer.delta() << std::endl;
    std::cout << "Digital Call: $" << digitalCallPricer() << ", Delta: " << digitalCallPricer.delta() << std::endl;
    std::cout << "Digital Put: $" << digitalPutPricer() << ", Delta: " << digitalPutPricer.delta() << std::endl;
    
    // CRR Pricer
    double up = 0.05;
    double down = -0.045;
    int depth = 5;
    CRRPricer crrCall(&call, depth, assetPrice, up, down, interestRate);
    CRRPricer crrPut(&put, depth, assetPrice, up, down, interestRate);
    std::cout << std::endl << "*** CRR ***" << std::endl;
    std::cout << "European Call: $" << crrCall() << std::endl;
    std::cout << "European Put: $" << crrPut() << std::endl;
    std::cout << "European Call (Closed-Form): $" << crrCall(true) << std::endl;
    std::cout << "European Put (Closed-Form): $" << crrPut(true) << std::endl;
    CRRPricer crrDigitalCall(&dcall, depth, assetPrice, up, down, interestRate);
    CRRPricer crrDigitalPut(&dput, depth, assetPrice, up, down, interestRate);
    std::cout << "Digital European Call: $" << crrDigitalCall() << std::endl;
    std::cout << "Digital European Put: $" << crrDigitalPut() << std::endl;
    std::cout << "Digital European Call (Closed-Form): $" << crrDigitalCall(true) << std::endl;
    std::cout << "Digital European Put (Closed-Form): $" << crrDigitalPut(true) << std::endl;
    
    double expiry = 5;
    int m = 10;
    std::vector<double> ts{};
    for(int i = 1; i <= m; i++){
        ts.push_back(((double)i / (double)m) * expiry);
    }
    
    AsianCallOption asianCall(ts, 101);
    std::cout << &asianCall << std::endl;
    BlackScholesMCPricer mcPricer(&asianCall, assetPrice, interestRate, vol);
    
    //mcPricer.generate(1);
    //std::cout << mcPricer.getNbPaths() << std::endl;
    //std::cout << mcPricer() << std::endl;
    
    
    
    return 0;
}
