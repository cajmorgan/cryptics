#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "../cryptics.h"


/** Random Prime Generator
*
**/
uint64_t cryptics_primes_random_prime(uint64_t high, uint64_t low) {
  if (low >= high)
    return -1;

  double random_decimals = 0;
  uint64_t random_integer = 0;
  while(random_decimals <= 0)
    random_decimals = cryptics_utilities_random_num();

  random_integer = (random_decimals * (high - low)) + low;

  while(cryptics_primes_primality_test(random_integer) == false)
    random_integer--;

  return random_integer;
}


