//
//  Option.cpp
//  Projet_IF2
//
//  Created by Arthur Cluet on 18/11/2022.
//

#include "Option.hpp"

//std::vector<double> Option::payoffPath(std::vector<double> St){
//    std::vector<double> Ht = std::vector<double>();
//    for(int i = 0; i < St.size(); i++){
//        Ht.push_back(payoff(St[i]));
//    }
//    return Ht;
//};

double Option::payoffPath(double a){
    return payoff(a);
}

bool Option::isAsianOption(){
    return false;
}
