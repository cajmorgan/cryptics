#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "rsa.h"
#include "../cryptics.h"

#define E 65537

uint64_t cryptics_rsa_32_generate_keys() {
  uint64_t rand_p, rand_q, prime_product, totient_product, private_exp;
  rand_p = cryptics_primes_random_prime(196611, 100000);
  rand_q = cryptics_primes_random_prime(21845, 10000);

  prime_product = rand_p * rand_q;
  totient_product = cryptics_general_lcm(rand_p-1, rand_q-1);
  private_exp = cryptics_general_mmi(E, totient_product);

  if (private_exp < 0) {
    return -1;
  }
  printf("P %ld\n", rand_p);
  printf("Q %ld\n", rand_q);
  printf("Prime Product: %ld\n", prime_product);
  printf("LCM: %ld\n", totient_product);
  printf("PRIVATE %ld\n", private_exp);
  return rand_p;
}
