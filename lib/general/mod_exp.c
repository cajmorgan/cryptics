#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "../cryptics.h"

/** Modulus of powered number
* An efficient way to calculate modulus of very large exponents,
* using exponentiation by squaring.
**/
int64_t cryptics_general_mod_exp(int64_t num, int64_t exp, int64_t mod) {
  int64_t res = 1;
  int64_t base = num;
  while (exp > 0) {
    if (exp & 1)
      res = cryptics_general_mod(res * base, mod);

    base = cryptics_general_mod(base * base, mod);
    exp = exp >> 1;
  }


  return res;
}


