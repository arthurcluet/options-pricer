# C++ Pricer

Object-oriented C++ Pricer for European options and digital options.
The pricer uses the Black-Scholes model or the Cox-Ross-Rubinstein model.

## Example

### Objects representing the options
```cpp
double interestRate = 0.01; // Interest rate
double vol = 0.1; // Volatility
double assetPrice = 100; // Asset price (t=0)
CallOption call(5, 101);
PutOption put(5, 101);
DigitalCallOption dcall(5, 101); // (expiry, strike)
DigitalPutOption dput(5, 101); // (expiry, strike)
```

### Black-Scholes model output
```cpp
*** Black Scholes ***
Call: $10.8293, Delta: 0.61444
Put: $6.90342, Delta: -0.38556
Digital Call: $0.553841, Delta: 0.0187135
Digital Put: $0.49743, Delta: -0.0187135
```

You can try the option evaluation with the CRR model by running `main.cpp`.

_Note: This version is incomplete and should be updated for asian and american options._
