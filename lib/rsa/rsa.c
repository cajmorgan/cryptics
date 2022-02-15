#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "rsa.h"
#include "../cryptics.h"

#define E 65537

int cryptics_rsa_32_generate_keys(struct rsa_32_public_key *public_key, struct rsa_32_private_key *private_key) {
  uint64_t rand_p, rand_q, modulus, totient_product, private_exp;
  rand_p = cryptics_primes_random_prime(196611, 100000);
  rand_q = cryptics_primes_random_prime(21845, 10000);

  modulus = rand_p * rand_q;
  totient_product = cryptics_general_lcm(rand_p-1, rand_q-1);
  private_exp = cryptics_general_mmi(E, totient_product);

  if (private_exp < 0) {
    return -1;
  }

  public_key->modulus = modulus;
  public_key->public_key_exponent = E;

  private_key->version = 1;
  private_key->modulus = modulus;
  private_key->public_key_exponent = E;
  private_key->private_key_exponent = private_exp;
  private_key->prime_p = rand_p;
  private_key->prime_q = rand_q;

  return 0;
}
