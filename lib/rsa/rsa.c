#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "../cryptics.h"

uint64_t cryptics_rsa_generate_keys() {
  uint64_t rand_p, rand_q, prime_product;
  rand_p = cryptics_primes_random_prime(100000000, 10000000);
  rand_q = cryptics_primes_random_prime(10000000, 1000000);
  prime_product = rand_p * rand_q;

  printf("%ld\n", prime_product);
  return rand_p;
}
