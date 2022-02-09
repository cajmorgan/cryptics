#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "../cryptics.h"

/** Primality test using
* n ∈ Z | P(n) = 6 + 6(n-1) ± 1 where n != 0 and P is a prime >= 5
*
**/
bool cryptics_primes_primality_test(uint64_t number) {
  if (number > UINT64_MAX) {
    fprintf(stderr, "Number too large, max 2⁶⁴ - 1");
  }

  if (number == 2 || number == 3)
    return true;

  if (number % 2 == 0 || number % 3 == 0) {
    return false;
  };

  for (int i = 6; i*i <= number; i += 6) {
    if (number % (i-1) == 0 || number % (i+1) == 0) {
      return false;
    }
  };

  return true;
}

/** Coprimality test using Euclidean Algorithm
* {a, b} ∈ Z | C(a, b) = C(b, a mod b) until b = 0 and a = 1
**/

bool cryptics_primes_coprimality_test(uint64_t number_one, uint64_t number_two) {
  if (number_one > UINT64_MAX || number_two > UINT64_MAX) {
    fprintf(stderr, "Number too large, max 2⁶⁴ - 1");
  }

  if (number_one == number_two) {
    if (cryptics_primes_primality_test(number_one))
      return 1;
    else
      return 0;
  }

  int gcd = cryptics_general_gcd(number_one, number_two);

  if (gcd == 1)
    return true;

  return false;
}


