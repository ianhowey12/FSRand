#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void fs_seed(int64_t seed);

// Uniform integer from 0 to 2^64 - 1
uint64_t fsi();

// Uniform integer from lower to upper bound
int64_t fsi_bounds(int64_t low, int64_t high);

// Uniform integer given lower bound and number of possible outcomes
int64_t fsi_range(int64_t min, uint64_t range);

// Uniform double from 0 to 1
double fsf();

// Uniform double from lower to upper bound
double fsf_bounds(double low, double high);

// Uniform double given lower bound and range of possible outcomes
double fsf_range(double min, double range);


// Linearly increasing double from 0 to 1
double fsf_inc();

// Linearly increasing double from lower to upper bound
double fsf_inc_bounds(double min, double max);

// Linearly increasing double given lower bound and range of possible outcomes
double fsf_inc_range(double min, double range);

// Linearly increasing integer from 2^-63 to 2^63 - 1
int64_t fsi_inc();

// Linearly increasing integer from lower to upper bound
int64_t fsi_inc_bounds(double min, double max);

// Linearly increasing integer given lower bound and number of possible outcomes
int64_t fsi_inc_range(double min, double range);


// Linearly decreasing double from 0 to 1
double fsf_dec();

// Linearly decreasing double from lower to upper bound
double fsf_dec_bounds(double min, double max);

// Linearly decreasing double given lower bound and range of possible outcomes
double fsf_dec_range(double min, double range);

// Linearly decreasing integer from 2^-63 to 2^63 - 1
int64_t fsi_dec();

// Linearly decreasing integer from lower to upper bound
int64_t fsi_dec_bounds(double min, double max);

// Linearly decreasing integer given lower bound and number of possible outcomes
int64_t fsi_dec_range(double min, double range);


// Triangular double from 0 to 1
double fsf_tri();

// Triangular double from lower to upper bound given mode
double fsf_tri_bounds(double min, double max, double mode);

// Triangular double given lower bound and range of possible outcomes and mode
double fsf_tri_range(double min, double range, double mode);

// Triangular integer from 2^-63 to 2^63 - 1
int64_t fsi_tri();

// Triangular integer from lower to upper bound given mode
int64_t fsi_tri_bounds(double min, double max, double mode);

// Triangular integer given lower bound and number of possible outcomes and mode
int64_t fsi_tri_range(double min, double range, double mode);


// Normal double with mean 0 and standard deviation 1
double fsf_n();

// Normal double given mean and standard deviation
double fsf_n_msd(double mean, double SD);

// Normal integer (rounded double) with mean 0 and standard deviation 1
int64_t fsi_n();

// Normal integer (rounded double) given mean and standard deviation
int64_t fsi_n_msd(double mean, double SD);


// Exponential double with mean 1
double fsf_exp();

// Exponential double given mean
double fsf_exp_mean(double mean);

// Exponential double given median
double fsf_exp_median(double median);

// Exponential integer with mean 1
int fsi_exp();

// Exponential integer given mean
int fsi_exp_mean(double mean);

// Exponential integer given median
int fsi_exp_median(double median);


// Bernoulli integer with probability of success 0.5
int fsi_ber();

// Bernoulli integer given probability of success
int fsi_ber_p(double p);


// Binomial integer for 1 trial with probability of success 0.5
int fsi_bin();

// Binomial integer given number of trials and probability of success
int fsi_bin_np(int n, double p);

// Approximate binomial integer given number of trials and probability of success
int fsi_binapprox_np(int n, double p);


// Poisson integer with mean 1
int fsi_poi();

// Poisson integer given 0 < mean < 600
int fsi_poi_mean(double mean);

// Approximate Poisson integer given mean > 0
int fsi_poiapprox_mean(double mean);