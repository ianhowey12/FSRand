# FSRand
A fast, simple random number generation header file for C/C++ general development. 42 RNG functions covering nine probability distributions. Also includes statistical tests and histogram visualization within tests.c.

All RNG functions are based on a core uniform uint64_t RNG. This function operates on its own previous output and the state of the RNG, both uint64_t values. This algorithm is done using only five mathematical operations, making it extremely fast.

The period of the RNG is 2^64. The state can be set using fs_seed(int64_t seed).

These algorithms are not suitable for cryptographic randomness.

There are 42 RNG functions covering the following nine distributions:
- Uniform
- Linearly increasing probability density
- Linearly decreasing probability density
- Triangular
- Normal
- Exponential
- Bernoulli
- Binomial
- Poisson

Many distributions contain functions that generate integers and others that generate decimals.

Functions whose names begin with fsi (FSRand integer) return a int64_t, uint64_t, or int.

Functions whose names begin with fsf (FSRand float) return a double.

For functions whose range is a user-defined range of values, either the lower and upper bound (inclusive) can be used, or the lower bound and number of possible values (for integer functions) or decimal range (for decimal functions) can be used. Functions containing _bounds take the bounds as input, whereas functions containing _range take the lower bound and range as input.
