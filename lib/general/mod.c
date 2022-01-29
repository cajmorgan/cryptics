#include <math.h>
#include <stdint.h>
#include <stdio.h>

/** Modulus Operator
* Real modulus operator as '%' in C is only a "remainder operator".
* This short function will return correct positive remainders.
**/

uint64_t cryptics_general_mod(int64_t a, int64_t m) {
  int64_t q = a/m;
  if (q <= 0)
    q -= 1;

  int r = a - (q * m);

  return r;
}
