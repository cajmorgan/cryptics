#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** Primality test using
* n ∈ Z | P(n) = 6 + 6(n-1) ± 1 where n != 0 and P is a prime >= 5
*
**/
bool cryptics_primes_primality_test(unsigned long long number) {
  if (number > 0xFFFFFFFFFFFFFFFF) {
    fprintf(stderr, "Number too large, max 2⁶⁴ - 1");
  }

  if (number == 2 || number == 3)
    return true;

  if (number % 2 == 0 || number % 3 == 0) {
    return false;
  };

  for (int i = 6; i*i <= number; i += 6) {
    if (number % i-1 == 0 || number % i+1 == 0) {
      return false;
    }
  };

  return true;
}


