#include <iostream>
#include <random>

int nums[781];

void initialize() {
	srand((unsigned) time(NULL));
	for (int i = 0; i < 781; i++) {
		nums[i] = rand();
	}
}