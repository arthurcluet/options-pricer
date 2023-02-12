//
//  CRRPricer.cpp
//  Projet_IF2
//
//  Created by Arthur Cluet on 20/12/2022.
//

#include "CRRPricer.hpp"

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate){
    _option = option;
    _depth = depth;
    _asset_price = asset_price;
    _up = up;
    _down = down;
    _interest_rate = interest_rate;
    _computed = false;
    if(option->isAsianOption()){
        throw std::invalid_argument("Option parameter can't be an Asian option");
    }
    if(_down < _interest_rate && _interest_rate < _up){
        _tree.setDepth(depth);
    } else {
        throw std::invalid_argument("Parameters must verify D < R < U");
    }
}

void CRRPricer::compute(){
    double q = (_interest_rate - _down) / (_up - _down);
    for(int i = _depth; i >= 0; i--){
        for(int j = 0; j <= i; j++){
            if(i == _depth){
                _tree.setNode(i, j, _option->payoff(_asset_price * pow(1+_up, j) * pow(1+_down, i-j)));
            } else {
                _tree.setNode(i, j, (q * _tree.getNode(i+1, j+1) + (1-q)*_tree.getNode(i+1, j) ) / (1+_interest_rate));
            }
        }
    }
    _computed = true;
}

double CRRPricer::get(int n, int i){
    return _tree.getNode(n, i);
}

double fact(int n){
    double a = 1;
    if(n <= 0) return a;
    for(int i = 1; i <= n; i++){
        a *= i;
    }
    return a;
}

double CRRPricer::operator()(bool closed_form){
    if(!_computed) compute();
    if(closed_form){
        double H = 0;
        double q = (_interest_rate - _down) / (_up - _down);
        for(int i = 0; i <= _depth; i++){
            H += fact(_depth)/(fact(i)*fact(_depth - i))*pow(q, i)*pow(1-q, _depth - i)*_option->payoff(_asset_price * pow(1+_up, i) * pow(1+_down, _depth-i));
        }
        H *= pow(1+_interest_rate, _depth);
        return H;
    } else {
        return _tree.getNode(0, 0);
    }
}
