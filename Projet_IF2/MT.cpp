//
//  MT.cpp
//  Projet_IF2
//
//  Created by Arthur Cluet on 20/12/2022.
//

#include "MT.hpp"

MT MT::s;
MT& MT::getInstance(){
    return s;
}
MT::MT(){
    //std::cout << "Constructor" << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
}
std::mt19937 & MT::IGen(){
    return mt;
}
std::mt19937 & MT::Gen(){
    return getInstance().IGen();
}
double MT::rand_unif(){
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(MT::Gen());
}
double MT::rand_norm() {
    std::normal_distribution<double> dis(0.0, 1.0);
    return dis(MT::Gen());
}
