#ifndef PRIMES_H_INCLUDED
#define PRIMES_H_INCLUDED

  #include <stdbool.h>
  #include <stdint.h>

  bool cryptics_primes_primality_test(uint64_t);
  bool cryptics_primes_coprimality_test(uint64_t number_one, uint64_t number_two);
  uint64_t cryptics_primes_random_prime(uint64_t high, uint64_t low);

#endif // PRIMES_H_INCLUDED
