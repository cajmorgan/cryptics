#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "general.h"


/** Modular Multiplicative Inverse
* In general, the inverse of an element is x*y = 1 where y is the reverse of x.
* F.e 1/5 * 5/1
*
* Shortened mmi here, is the inverse of some n in a modular relation.
* A mmi only exists if a & b are co-prime. They can however exist
* as multiples of a & b if a & b is co-prime. For example, if a = 7 and b = 390,
* the mmi of 7 is 7⁻¹ = x (mod b) where x = -167. If a = 14 and b = 780,
* x and y is the same (-167 & 3) but the gcd is = 2, which mean we can factor out 2 from a & b
* and get back to the first statement. Also if both a and b are positive,
* either x or y coeffecients will be negative.
*
* What is a⁻¹ mod b?
* xa + yb = GCD(a,b) = 1
* -------------------
* xa + yb ≡ 1 (mod b)
* xa ≡ 1 - yb (mod b) // note that 1 - yb = xa
* xa ≡ 1 (mod b)
* x ≡ 1/a (mod b)
* x ≡ a⁻¹ (mod b)
* Therefore, coeffiecent x mod b is the same as the inverse of a mod b
**/
uint64_t cryptics_general_mmi(uint64_t a, uint64_t m) {
  int64_t *gcd_ext = (int64_t *)malloc(sizeof(int64_t) * 3);
  if(gcd_ext[0] != 1) {
    return -1;
  }

  cryptics_general_gcd_extended(a, m, gcd_ext);

  uint64_t res = cryptics_general_mod(gcd_ext[1], m);
  free(gcd_ext);

  return res;
}
