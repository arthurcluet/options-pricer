//
//  CRRPricer.hpp
//  Projet_IF2
//
//  Created by Arthur Cluet on 20/12/2022.
//

#ifndef CRRPricer_hpp
#define CRRPricer_hpp

#include <stdio.h>
#include "Option.hpp"
#include "BinaryTree.hpp"
#include <math.h>
#include <iostream>

class CRRPricer {
private:
    Option* _option;
    int _depth;
    double _asset_price;
    double _up;
    double _down;
    double _interest_rate;
    bool _computed;
    BinaryTree<double> _tree;
public:
    CRRPricer(Option*, int, double, double, double, double);
    void compute();
    double get(int, int);
    double operator()(bool closed_form = false);
};



#endif /* CRRPricer_hpp */
