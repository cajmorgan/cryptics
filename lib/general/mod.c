#include <math.h>
#include <stdlib.h>
#include <stdint.h>

/** Modulus Operator
* Real modulus operator as '%' in C is only a "remainder operator".
* This short function will return correct positive remainders.
* ----------------
* 11 mod 3 = 2 where q = 3 (3 * 3 = 9, 11 - 9 = 2)
* OR 11 / 3 = 3.666... ⌊3⌋.
* 3 fits evenly 3 times in 11, q = 9 r = 2
* 2/3 = 0.666... + 3 = 3.666...
* What is -11 mod 3? A remainder is always positive.
* -11/3 = -3.666... ⌊-4⌋. (-4 * 3 = -12, -11 - (-12) = 1)
* in a "q r relationship", q is always LESS than q + r and r is always positive.
* f(n) = 0 - (3n - 1) until f(n) < -11 (q + r)
* f(5) = 0 - (3 * 4) = -12
* r = a - q
* r = -11 - (-12)
* r = 1
**/


uint64_t cryptics_general_mod(int64_t a, int64_t m) {
  if (m == 0)
    return -1;

  int64_t q = a/m;
  if (q == 0 && a < 0 && a < m)
    q = -1;
  if (q < 0)
    q -= 1;

  int64_t r = a - (q * m);

  return abs(r);
}
