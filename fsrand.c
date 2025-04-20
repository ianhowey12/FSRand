#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "tables.c"


uint64_t fs_prev = 0x947b19e3fd46b7a5;
uint64_t fs_state = 0;

void fs_seed(int64_t seed) {
    fs_prev = 0x947b19e3fd46b7a5;
    fs_state = seed;
}

// Uniform integer from 0 to 2^64 - 1
uint64_t fsi() {
    fs_prev = (fs_prev + (fs_prev / 2) + fs_state++) * 0x681ac9427d5fe8b3;
    return fs_prev;
}

// Uniform integer from lower to upper bound
int64_t fsi_bounds(int64_t min, int64_t max) {
    return min + (fsi() % (max - min + 1));
}

// Uniform integer given lower bound and number of possible outcomes
int64_t fsi_range(int64_t min, uint64_t range) {
    return min + (fsi() % range);
}

// Uniform double from 0 to 1
double fsf() {
    return (double)fsi() / 18446744073709551616.0;
}

// Uniform double from lower to upper bound
double fsf_bounds(double min, double max) {
    return min + (max - min) * ((double)fsi() / 18446744073709551616.0);
}

// Uniform double given lower bound and range of possible outcomes
double fsf_range(double min, double range) {
    return min + range * ((double)fsi() / 18446744073709551616.0);
}

// Linearly increasing double from 0 to 1
double fsf_inc() {
    return sqrt(fsf());
}

// Linearly increasing double from lower to upper bound
double fsf_inc_bounds(double min, double max) {
    return min + (max - min) * sqrt(fsf());
}

// Linearly increasing double given lower bound and range of possible outcomes
double fsf_inc_range(double min, double range) {
    return min + range * sqrt(fsf());
}

// Linearly increasing integer from -2^63 to 2^63 - 1
int64_t fsi_inc() {
    return floor((double)0xffffffffffffffff * sqrt(fsf()) - (double)0x7fffffffffffffff);
}

// Linearly increasing integer from lower to upper bound
int64_t fsi_inc_bounds(double min, double max) {
    return floor(min + (max - min) * sqrt(fsf()));
}

// Linearly increasing integer given lower bound and number of possible outcomes
int64_t fsi_inc_range(double min, double range) {
    return floor(min + range * sqrt(fsf()));
}

// Linearly decreasing double from 0 to 1
double fsf_dec() {
    return 1.0 - sqrt(fsf());
}

// Linearly decreasing double from lower to upper bound
double fsf_dec_bounds(double min, double max) {
    return max - (max - min) * sqrt(fsf());
}

// Linearly decreasing double given lower bound and range of possible outcomes
double fsf_dec_range(double min, double range) {
    return min + range - range * sqrt(fsf());
}

// Linearly decreasing integer from -2^63 to 2^63 - 1
int64_t fsi_dec() {
    return floor((double)0x7fffffffffffffff - (double)0xffffffffffffffff * sqrt(fsf()));
}

// Linearly decreasing integer from lower to upper bound
int64_t fsi_dec_bounds(double min, double max) {
    return floor(max - (max - min) * sqrt(fsf()));
}

// Linearly decreasing integer given lower bound and number of possible outcomes
int64_t fsi_dec_range(double min, double range) {
    return floor(min + range - range * sqrt(fsf()));
}

// Triangular double from 0 to 1 with mode 0.5
double fsf_tri() {
    double x = fsf();
    if (x < 0.5) {
        return sqrt(x * 0.5);
    }
    return 1.0 - sqrt((1.0 - x) * 0.5);
}

// Triangular double from lower to upper bound given mode
double fsf_tri_bounds(double min, double max, double mode) {
    double x = fsf();
    double range = max - min;
    if (x < (mode - min) / range) {
        return min + sqrt(x * range * (mode - min));
    }
    return max - sqrt((1.0 - x) * range * (max - mode));
}

// Triangular double given lower bound and range of possible outcomes and mode
double fsf_tri_range(double min, double range, double mode) {
    double x = fsf();
    double max = min + range;
    if (x < (mode - min) / range) {
        return min + sqrt(x * range * (mode - min));
    }
    return max - sqrt((1.0 - x) * range * (max - mode));
}

// Triangular integer from -2^63 to 2^63 - 1
int64_t fsi_tri() {
    double x = fsf();
    if (x < 0.5) {
        return floor((double)LLONG_MIN + sqrt(x) * 13043817825000000000.0);
    }
    return floor((double)0xffffffffffffffff - sqrt(1.0 - x) * 13043817825000000000.0);
}

// Triangular integer from lower to upper bound given mode
int64_t fsi_tri_bounds(double min, double max, double mode) {
    double x = fsf();
    double range = max - min;
    if (x < (mode - min) / range) {
        return min + sqrt(x * range * (mode - min));
    }
    return max - sqrt((1.0 - x) * range * (max - mode));
}

// Triangular integer given lower bound and number of possible outcomes and mode
int64_t fsi_tri_range(double min, double range, double mode) {
    double x = fsf();
    double max = (double)min + (double)range;
    if (x < (mode - min) / range) {
        return min + sqrt(x * range * (mode - min));
    }
    return floor(max - sqrt((1.0 - x) * range * (max - mode)));
}

// Normal double with mean 0 and standard deviation 1
double fsf_n() {
    double p = fsf();
    int ip;
    if (p <= 0.5) {
        if (p > 0.01) {
            p = (0.5 - p) * 200.0;
            ip = (int)p;
            return 0.0 - (fsNormalTable1[ip] + (p - ip) * (fsNormalTable1[ip + 1] - fsNormalTable1[ip]));
        }
        else {
            if (p >= 0.0001) {
                p = (0.01 - p) * 10000.0;
                ip = (int)p;
                return 0.0 - (fsNormalTable2[ip] + (p - ip) * (fsNormalTable2[ip + 1] - fsNormalTable2[ip]));
            }
            else {
                p = (0.0001 - p) * 1000000.0;
                ip = (int)p;
                return 0.0 - (fsNormalTable3[ip] + (p - ip) * (fsNormalTable3[ip + 1] - fsNormalTable3[ip]));
            }
        }
    }
    else {
        if (p <= 0.99) {
            p = (p - 0.5) * 200.0;
            ip = (int)p;
            return fsNormalTable1[ip] + (p - ip) * (fsNormalTable1[ip + 1] - fsNormalTable1[ip]);
        }
        else {
            if (p <= 0.9999) {
                p = (p - 0.99) * 10000.0;
                ip = (int)p;
                return fsNormalTable2[ip] + (p - ip) * (fsNormalTable2[ip + 1] - fsNormalTable2[ip]);
            }
            else {
                p = (p - 0.9999) * 1000000.0;
                ip = (int)p;
                return fsNormalTable3[ip] + (p - ip) * (fsNormalTable3[ip + 1] - fsNormalTable3[ip]);
            }
        }
    }
}

// Normal double given mean and standard deviation
double fsf_n_msd(double mean, double SD) {
    return mean + fsf_n() * SD;
}

// Normal integer (rounded double) with mean 0 and standard deviation 1
int64_t fsi_n() {
    return round(fsf_n());
}

// Normal integer (rounded double) given mean and standard deviation
int64_t fsi_n_msd(double mean, double SD) {
    return round(mean + fsf_n() * SD);
}

// Exponential double with mean 1
double fsf_exp() {
    return -1.0 * log(fsf());
}

// Exponential double given mean
double fsf_exp_mean(double mean) {
    return -1.0 * mean * log(fsf());
}

// Exponential double given median
double fsf_exp_median(double median) {
    return median * log(0.5) * log(fsf());
}

// Exponential integer (rounded down) with mean 1
int fsi_exp() {
    return floor(-1.0 * log(fsf()));
}

// Exponential integer (rounded down) given mean
int fsi_exp_mean(double mean) {
    return floor(-1.0 * mean * log(fsf()));
}

// Exponential integer (rounded down) given median
int fsi_exp_median(double median) {
    return floor(median * log(0.5) * log(fsf()));
}

// Bernoulli integer with probability of success 0.5
int fsi_ber() {
    return fsf() < 0.5;
}

// Bernoulli integer given probability of success
int fsi_ber_p(double p) {
    return fsf() < p;
}

// Binomial integer for 1 trial with probability of success 0.5
int fsi_bin() {
    return fsf() < 0.5;
}

// Binomial integer given number of trials and probability of success
int fsi_bin_np(int n, double p) {
    uint64_t c = 0;
    for (int i = 0; i < n; i++) {
        c += fsf() < p;
    }
    return c;
}

// Approximate binomial integer given number of trials and probability of success
int fsi_binapprox_np(int n, double p) {
    int c = n * p + fsf_n() * sqrt(n * p * (1 - p));
    if (c > n) return n;
    if (c < 0) return 0;
    return c;
}

// Poisson integer with mean 1
int fsi_poi() {
    double limit = exp(-1.0);
    int k = 0;
    double x = fsf();
    double p;
    while (x > limit) {
        x *= fsf();
        k++;
    }
    return k;
}

// Poisson integer given 0 < mean < 600
int fsi_poi_mean(double mean) {
    double limit = exp(-1.0 * mean);
    int k = 0;
    double x = fsf();
    double p;
    while (x > limit) {
        x *= fsf();
        k++;
    }
    return k;
}

// Approximate Poisson integer given mean > 0
int fsi_poiapprox_mean(double mean) {
    int c = round(mean + fsf_n() * sqrt(mean));
    if (c < 0) return 0;
    return c;
}