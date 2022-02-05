#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>



/** Random Prime Generator
* Two first arguments takes two limits, high and low for the prime limit.
* The seed i
*
*
**/
uint64_t cryptics_primes_random_prime(uint64_t high, uint64_t low, uint64_t seed) {
  if (seed < 0xf4240) {
    fprintf(stderr, "Seed needs to be larger than 0xf4240");
    return -1;
  }

  uint64_t seed_cpy = seed;
  int counter = 0;
  while(seed_cpy != 0) {
    seed_cpy /= 10;
    counter += 1;
  }

  uint64_t random_divisor = generate_random_number();
  double random_float = random_divisor / seed;

  printf("%f", random_float);
}


