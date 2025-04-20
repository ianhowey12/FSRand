#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "fsrand.h"

// Test and print sample deviations, outcomes, and differences of last 8 bits of uniform rng. n is the number of random values from the fsi() function to print. Essentially a Monte Carlo simulation.
static void printUniformDistribution(long long n) {

	long long* outcomes = (long long*)calloc(256, sizeof(long long));
	long long* differences = (long long*)calloc(256, sizeof(long long));

	int previous = 0;

	uint8_t r = 0;


	for (int i = 0; i < 256; i++) {
		outcomes[i] = 0;
		differences[i] = 0;
	}

	// sample the distribution of outcomes
	for (long long i = 0; i < n; i++) {
		r = fsi_range(0, 256);

		outcomes[r]++;
		differences[(r - previous + 256) % 256]++;

		previous = r;
	}

	double outcomeMean = 0;
	double differenceMean = 0;
	for (int i = 0; i < 256; i++) {
		outcomeMean += outcomes[i];
		differenceMean += differences[i];
	}
	outcomeMean /= 256.0;
	differenceMean /= 256.0;

	double outcomeSD = 0;
	double differenceSD = 0;
	for (int i = 0; i < 256; i++) {
		outcomeSD += (outcomes[i] - outcomeMean) * (outcomes[i] - outcomeMean);
		differenceSD += (differences[i] - differenceMean) * (differences[i] - differenceMean);
	}
	outcomeSD = sqrt(outcomeSD / 256.0);
	differenceSD = sqrt(differenceSD / 256.0);


	// print the probability difference of obtaining a 0 sample random number (least random outcome using this algorithm) from the average sample random number probability
	printf("Probability deviation of 0 from average result: %.20lf ", ((double)outcomes[0] / (double)n) - 0.00390625); printf("\n\n");

	// print the outcomes
	printf("Outcomes: "); for (int i = 0; i < 256; i++) { printf("%lli ", outcomes[i]);} printf("\n\n");

	// print the outcome standard deviation
	printf("SD of outcomes: "); printf("%f", outcomeSD); printf("\n\n");

	// print the differences between consecutive sampled random numbers mod 256
	printf("Differences: "); for (int i = 0; i < 256; i++) { printf("%lli ", differences[i]);} printf("\n\n");

	// print the difference standard deviation
	printf("SD of differences: "); printf("%f", differenceSD); printf("\n\n");

}

// Print sample values from uniform rng. n is the number of random values from the fsi() function to print
static void printUniformSampleValues(int n) {
	printf("%i sample values:\n", n);
	for (int i = 0; i < n; i++) {
		printf("%lli\n", fsi());
	}
	printf("\n");
}

// Print bits of sample values from uniform rng. n is the number of random values from the fsi() function to print
static void printUniformSampleBits(int n) {
	printf("%i sample values as bits:\n", n);
	uint64_t r;
	char bits[64] = { 0 };
	for (int i = 0; i < n; i++) {
		r = fsi();
		for (int j = 63; j >= 0; j--) {
			bits[j] = (r % 2) + 48;
			r /= 2;
		}
		printf("%s\n", bits);
	}
	printf("\n");
}

// Print sample values from all 42 rng functions. n is the number of random values from each function to print.
static void printAllSampleValues(int n) {

	printf("\n\nUniform integer from 0 to 2^64 - 1: ");
	for (int i = 0; i < n; i++) {
		printf("%llu ", fsi());
	}
	printf("\n\nUniform integer from lower to upper bound: ");
	for (int i = 0; i < n; i++) {
		printf("%lli ", fsi_bounds(-1000, 1000));
	}
	printf("\n\nUniform integer given lower bound and number of possible outcomes: ");
	for (int i = 0; i < n; i++) {
		printf("%lli ", fsi_range(-1000, 2000));
	}
	printf("\n\nUniform double from 0 to 1: ");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf());
	}
	printf("\n\nUniform double from lower to upper bound: ");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf_bounds(-1000.0, 1000.0));
	}
	printf("\n\nUniform double given lower bound and range of possible outcomes: ");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf_range(-1000.0, 2000.0));
	}
	
	printf("\n\nLinearly increasing double from 0 to 1: ");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf_inc());
	}
	printf("\n\nLinearly increasing double from lower to upper bound: ");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf_inc_bounds(-1000.0, 1000.0));
	}
	printf("\n\nLinearly increasing double given lower bound and range of possible outcomes: ");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf_inc_range(-1000.0, 2000.0));
	}
	printf("\n\nLinearly increasing integer from 2^-63 to 2^63 - 1: ");
	for (int i = 0; i < n; i++) {
		printf("%lli ", fsi_inc());
	}
	printf("\n\nLinearly increasing integer from lower to upper bound: ");
	for (int i = 0; i < n; i++) {
		printf("%lli ", fsi_inc_bounds(-1000, 1000));
	}
	printf("\n\nLinearly increasing integer given lower bound and number of possible outcomes: ");
	for (int i = 0; i < n; i++) {
		printf("%lli ", fsi_inc_range(-1000, 2000));
	}
	
	printf("\n\nLinearly decreasing double from 0 to 1: ");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf_dec());
	}
	printf("\n\nLinearly decreasing double from lower to upper bound");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf_dec_bounds(-1000.0, 1000.0));
	}
	printf("\n\nLinearly decreasing double given lower bound and range of possible outcomes: ");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf_dec_range(-1000.0, 2000.0));
	}
	printf("\n\nLinearly decreasing integer from 2^-63 to 2^63 - 1: ");
	for (int i = 0; i < n; i++) {
		printf("%lli ", fsi_dec());
	}
	printf("\n\nLinearly decreasing integer from lower to upper bound: ");
	for (int i = 0; i < n; i++) {
		printf("%lli ", fsi_dec_bounds(-1000.0, 1000.0));
	}
	printf("\n\nLinearly decreasing integer given lower bound and number of possible outcomes: ");
	for (int i = 0; i < n; i++) {
		printf("%lli ", fsi_dec_range(-1000.0, 2000.0));
	}

	printf("\n\nTriangular double from 0 to 1: ");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf_tri());
	}
	printf("\n\nTriangular double from lower to upper bound given mode: ");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf_tri_bounds(-1000.0, 1000.0, 500.0));
	}
	printf("\n\nTriangular double given lower bound and range of possible outcomes and mode: ");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf_tri_range(-1000.0, 2000.0, 500.0));
	}
	printf("\n\nTriangular integer from 2^-63 to 2^63 - 1: ");
	for (int i = 0; i < n; i++) {
		printf("%lli ", fsi_tri());
	}
	printf("\n\nTriangular integer from lower to upper bound given mode: ");
	for (int i = 0; i < n; i++) {
		printf("%lli ", fsi_tri_bounds(-1000.0, 1000.0, 500.0));
	}
	printf("\n\nTriangular integer given lower bound and number of possible outcomes and mode: ");
	for (int i = 0; i < n; i++) {
		printf("%lli ", fsi_tri_range(-1000.0, 2000.0, 500.0));
	}
	
	printf("\n\nNormal double with mean 0 and standard deviation 1: ");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf_n());
	}
	printf("\n\nNormal double given mean and standard deviation: ");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf_n_msd(10.0, 4.0));
	}
	printf("\n\nNormal integer (rounded double) with mean 0 and standard deviation 1: ");
	for (int i = 0; i < n; i++) {
		printf("%lli ", fsi_n());
	}
	printf("\n\nNormal integer (rounded double) given mean and standard deviation: ");
	for (int i = 0; i < n; i++) {
		printf("%lli ", fsi_n_msd(10.0, 4.0));
	}
	
	printf("\n\nExponential double with mean 1: ");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf_exp());
	}
	printf("\n\nExponential double given mean: ");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf_exp_mean(5.0));
	}
	printf("\n\nExponential double given median: ");
	for (int i = 0; i < n; i++) {
		printf("%f ", fsf_exp_median(5.0));
	}
	printf("\n\nExponential integer with mean 1: ");
	for (int i = 0; i < n; i++) {
		printf("%i ", fsi_exp());
	}
	printf("\n\nExponential integer given mean: ");
	for (int i = 0; i < n; i++) {
		printf("%i ", fsi_exp_mean(5.0));
	}
	printf("\n\nExponential integer given median: ");
	for (int i = 0; i < n; i++) {
		printf("%i ", fsi_exp_median(5.0));
	}

	printf("\n\nBernoulli integer with probability of success 0.5: ");
	for (int i = 0; i < n; i++) {
		printf("%i ", fsi_ber());
	}
	printf("\n\nBernoulli integer given probability of success: ");
	for (int i = 0; i < n; i++) {
		printf("%i ", fsi_ber_p(0.7));
	}

	printf("\n\nBinomial integer for 1 trial with probability of success 0.5: ");
	for (int i = 0; i < n; i++) {
		printf("%i ", fsi_bin());
	}
	printf("\n\nBinomial integer given number of trials and probability of success: ");
	for (int i = 0; i < n; i++) {
		printf("%i ", fsi_bin_np(20, 0.7));
	}
	printf("\n\nApproximate binomial integer given number of trials and probability of success: ");
	for (int i = 0; i < n; i++) {
		printf("%i ", fsi_binapprox_np(2000, 0.7));
	}

	printf("\n\nPoisson integer with mean 1: ");
	for (int i = 0; i < n; i++) {
		printf("%i ", fsi_poi());
	}
	printf("\n\nPoisson integer given 0 < mean < 600: ");
	for (int i = 0; i < n; i++) {
		printf("%i ", fsi_poi_mean(5.0));
	}
	printf("\n\nApproximate Poisson integer given mean > 0: ");
	for (int i = 0; i < n; i++) {
		printf("%i ", fsi_poiapprox_mean(5000.0));
	}
	printf("\n");
}

// Print sample values from the chosen function. n is the number of random values from each function to print.
static void printSpecificSampleValues(int n) {

	for (int i = 0; i < n; i++) {
		// this function is customizable
		printf("%f ", fsf_exp_mean(10.0));
	}
	printf("\n\n");
}

// Print a histogram for the random values generated by the chosen function. n is the number of random values to sample. min and max are the histogram endpoint values.
static void printHistogram(long long n, double min, double max, int numBars) {
	if (numBars < 1 || numBars > 200) {
		printf("The histogram could not be displayed because the number of bars is out of the range 1 <= numBars <= 200.\n\n");
		return;
	}
	if (min >= max) {
		printf("The histogram could not be displayed because the lower endpoint is greater than or equal to the higher endpoint.\n\n");
		return;
	}
	if (n < 1) {
		printf("The histogram could not be displayed because the number of random values to sample is less than 1.\n\n");
		return;
	}

	long long* counts = calloc(numBars, sizeof(long long));
	double range = max - min;
	double x;
	long long totalCount = 0;

	for (long long i = 0; i < n; i++) {
		// this function is customizable
		x = (double)fsf_exp_mean(10.0);
		if (x >= min && x < max) {
			counts[(int)((double)numBars * (x - min) / range)]++;
			totalCount++;
		}
	}
	
	double maxValue = (double)counts[0];
	int maxIndex = 0;
	for (int i = 1; i < numBars; i++) {
		if (counts[i] > (double)maxValue) {
			maxValue = counts[i];
			maxIndex = i;
		}
	}
	if (maxValue == 0.0) {
		printf("No data sampled fell within the histogram's display range.\n\n");
		return;
	}

	int height = 20;

	for (int j = 0; j < numBars; j++) {
		printf("-");
	}
	printf("\n");

	for (int i = 0; i < height; i++) {
		printf("|");
		for (int j = 0; j < numBars; j++) {
			if ((double)counts[j] >= maxValue * (double)(height - i) / (double)height) {
				printf("#");
			}
			else {
				printf(" ");
			}
		}

		printf("|\n");
	}

	for (int j = 0; j < numBars; j++) {
		printf("-");
	}
	printf("\n\n");

	printf("%lli out of %lli sampled random values are shown here.\nThe lower end is %f and the higher end is %f.\nThere are %i bars, so each bar represents a range of values equal to %f.\n\n",
		totalCount, n, min, max, numBars, range / (double)numBars);
}

// Test the rng functions to ensure high statistical quality. All tests have customizable inputs.
static void testDistributions() {

	//printUniformDistribution(100000000);
	//printUniformSampleValues(100);
	//printUniformSampleBits(100);
	//printAllSampleValues(50);
	//printSpecificSampleValues(1000);
	printHistogram(100000, 0.0, 40.0, 160);
}