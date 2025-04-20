#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "tests.c"
#include "fsrand.h"

int main(void) {

	// see tests.c for info on testing the rng
	testDistributions();

	return 0;
}