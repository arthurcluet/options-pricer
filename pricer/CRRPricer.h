#pragma once

#include "Option.h"
#include "BinaryTree.h"
#include <math.h>

class CRRPricer
{
private:
    Option* _option;
    int _depth;
    double _asset_price;
    double _up;
    double _down;
    double _interest_rate;
    bool _computed;
    BinaryTree<double> _tree;
    BinaryTree<double> _Htree;
    BinaryTree<bool> _exerciseConditionTree; // American Options

    double fact(int n) {
        double a = 1;
        if (n <= 0) return a;
        for (int i = 1; i <= n; i++) {
            a *= i;
        }
        return a;
    }

    double power(double x, int n) {
        double result = 1.0;
        while (n != 0) {
            if (n % 2 == 0) {
                x *= x;
                n /= 2;
            }
            else {
                result *= x;
                n -= 1;
            }
        }
        return result;
    }

public:
    CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate) {
        if (option->isAsianOption()) {
            throw invalid_argument("CRRPricer doesnt accept asian option");
        }
        _option = option;
        _depth = depth;
        _asset_price = asset_price;
        _up = up;
        _down = down;
        _interest_rate = interest_rate;
        _computed = false;
        // Arbitrage check
        if (_down < _interest_rate && _interest_rate < _up) {
            _tree.setDepth(depth);
            _Htree.setDepth(depth);
            _exerciseConditionTree.setDepth(_depth);
        }
        else {
            throw std::invalid_argument("Parameters must verify D < R < U");
        }
    }

    CRRPricer(Option* option, int depth, double asset_price, double r, double sigma) {
        if (option->isAsianOption()) {
            throw invalid_argument("CRRPricer doesnt accept asian option");
        }
        _option = option;
        _depth = depth;
        _asset_price = asset_price;
        double h = _option->getExpiry() / (double)depth;
        _up = exp( (r + sigma*sigma/2)*h + sigma*sqrt(h) ) - 1;
        _down = exp((r + sigma * sigma / 2) * h - sigma * sqrt(h)) - 1;
        _interest_rate = exp(r*h) - 1;
        _computed = false;


            _tree.setDepth(depth);
            _Htree.setDepth(depth);
            _exerciseConditionTree.setDepth(_depth);
        
    }

    void compute() {
        double q = (_interest_rate - _down) / (_up - _down);
        // Loop to set S(n,i) values
        for (int i = _depth; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                //if (i == _depth) {

                    //_tree.setNode(i, j, _option->payoff(_asset_price * power(1 + _up, j) * power(1 + _down, i - j)));
                //}
                //else {
                    //_tree.setNode(i, j, (q * _tree.getNode(i + 1, j + 1) + (1 - q) * _tree.getNode(i + 1, j)) / (1 + _interest_rate));
                //}
                _tree.setNode(i, j, _asset_price * power(1 + _up, j) * power(1 + _down, i - j));
            }
        }

        // Loop to set H(n,i) values

        for (int i = _depth; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                if (i == _depth) {
                    _Htree.setNode(i, j, _option->payoff(_tree.getNode(i, j)));
                }
                else {
                    //_tree.setNode(i, j, (q * _tree.getNode(i + 1, j + 1) + (1 - q) * _tree.getNode(i + 1, j)) / (1 + _interest_rate));
                    if (_option->isAmericanOption()) {
                        // Option américaine
                        double continuationValue = (q * _Htree.getNode(i + 1, j + 1) + (1 - q) * _Htree.getNode(i + 1, j)) / (1 + _interest_rate);
                        double intrinsicValue = _option->payoff(_tree.getNode(i, j));
                        _exerciseConditionTree.setNode(i, j, intrinsicValue >= continuationValue);
                        _Htree.setNode(i, j, _exerciseConditionTree.getNode(i, j) ? intrinsicValue : continuationValue);
                    }
                    else {
                        // Option non américaine
                        double Hni = (q * _Htree.getNode(i + 1, j + 1) + (1 - q) * _Htree.getNode(i + 1, j)) / (1 + _interest_rate);
                        _Htree.setNode(i, j, Hni);
                    }

                }
            }
        }
        _computed = true;
    }
    double get(int n, int i) {
        return _Htree.getNode(n, i);
    }
    bool getExercise(int n, int i) {
        return _exerciseConditionTree.getNode(n, i);
    }
    double operator()(bool closed_form = false) {
        if (!_computed) compute();
        if (closed_form) {
            double H = 0;
            double q = (_interest_rate - _down) / (_up - _down);
            for (int i = 0; i <= _depth; i++) {
                H += fact(_depth) / (fact(i) * fact(_depth - i)) * power(q, i) * power(1 - q, _depth - i) * _option->payoff(_asset_price * power(1 + _up, i) * power(1 + _down, _depth - i));
            }
            H *= power(1 + _interest_rate, _depth);
            return H;
        }
        else {
            return _Htree.getNode(0, 0);
        }
    }
};


