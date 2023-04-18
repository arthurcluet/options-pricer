#pragma once

#include <vector>

using namespace std;

class Option
{
protected:
    double _expiry;

public:
    Option(double expiry) : _expiry(expiry) {};
    virtual double payoff(double) = 0;
    virtual double payoffPath(vector<double> a) {
        return payoff(a.back());
    };
    double getExpiry() {
        return _expiry;
    };
    virtual bool isAsianOption() { return false; }
    virtual bool isAmericanOption() { return false; }
};