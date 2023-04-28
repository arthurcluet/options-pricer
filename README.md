# C++ Options Pricer

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)

Object-oriented C++ Pricer for:
- European options
- Digital options
- Asian options
- American options


The pricer implements the Black Scholes model as well as the Cox-Ross-Rubinstein model.

## Examples

### European & digital options

- `CallOption`
- `PutOption`
- `DigitalCallOption`
- `DigitalPutOption`

```cpp
double S0(100.), K(101.), T(5), r(0.01), sigma(0.1);
CallOption opt1(T, K);
DigitalPutOption opt2(T, K);

// Black Scholes model
BlackScholesPricer pricer1(&opt1, S0, r, sigma);
std::cout << "BlackScholesPricer price=" << pricer1() << ", delta=" << pricer1.delta() << std::endl;

BlackScholesPricer pricer2(&opt2, S0, r, sigma);
std::cout << "BlackScholesPricer price=" << pricer2() << ", delta=" << pricer2.delta() << std::endl;
std::cout << std::endl;

// CRR Model

int N(150);
double U = exp(sigma * sqrt(T / N)) - 1.0;
double D = exp(-sigma * sqrt(T / N)) - 1.0;
double R = exp(r * T / N) - 1.0;

CRRPricer crr_pricer1(&opt1, N, S0, U, D, R);
std::cout << "Calling CRR pricer with depth=" << N << std::endl;
std::cout << std::endl;
std::cout << "CRR pricer computed price=" << crr_pricer1() << std::endl;
std::cout << "CRR pricer explicit formula price=" << crr_pricer1(true) << std::endl;
std::cout << endl;
```

### Asian options

```cpp
double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
std::vector < Option * > opt_ptrs;
std::vector < double > fixing_dates;
for (int i = 1; i <= 5; i++) {
  fixing_dates.push_back(0.1 * i);
}
opt_ptrs.push_back(new AsianCallOption(fixing_dates, K));
opt_ptrs.push_back(new AsianPutOption(fixing_dates, K));

std::vector < double > ci;
BlackScholesMCPricer * pricer;

for (auto & opt_ptr: opt_ptrs) {
  pricer = new BlackScholesMCPricer(opt_ptr, S0, r, sigma);
  do {
    pricer -> generate(10);
    ci = pricer -> confidenceInterval();
  } while (ci[1] - ci[0] > 1e-2 && pricer -> getNbPaths() < 10000);
  std::cout << "nb samples: " << pricer -> getNbPaths() << std::endl;
  std::cout << "price: " << ( * pricer)() << std::endl << std::endl;
  delete pricer;
  delete opt_ptr;
}
```

### American options

- `AmericanCallOption`
- `AmericanPutOption`

```cpp
double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
std::vector<Option*> opt_ptrs;
opt_ptrs.push_back(new AmericanCallOption(T, K));
opt_ptrs.push_back(new AmericanPutOption(T, K));

CRRPricer* pricer;

for (auto& opt_ptr : opt_ptrs) {
    pricer = new CRRPricer(opt_ptr, 150, S0, r, sigma);
    pricer->compute();
    std::cout << "price: " << (*pricer)() << std::endl << std::endl;
    delete pricer;
    delete opt_ptr;
}
```
