#include <stdlib.h>
#include <stdint.h>
#include "general.h"

/** Euclidean algorithm, returns gcd **/

uint64_t cryptics_general_gcd(uint64_t a, uint64_t b) {
  uint64_t r = 1;

  while(r != 0) {
    r = a % b;
    a = b;
    b = r;
  }

  return a;
}


/** Extended Euclidean algorithm,
* returns an allocated* array with Bézout's coeffecients.
* index 0 = gcd(a, b)
* index 1 = coeffecient of a
* index 2 = coeffecients of b
* xa + yb = gcd(a, b)
**/
uint64_t *cryptics_general_gcd_extended(uint64_t a, uint64_t b) {
  uint64_t s[2] = {1, 0};
  uint64_t t[2] = {0, 1};
  uint64_t q, r;
  q = 0;
  r = 1;

  uint64_t s_temp, t_temp;
  s_temp = t_temp = 0;
  while(r != 0) {
    q = a / b;
    r = a - (b * q);
    a = b;
    b = r;

    s_temp = s[0] - (q * s[1]);
    t_temp = t[0] - (q * t[1]);

    s[0] = s[1];
    t[0] = t[1];
    s[1] = s_temp;
    t[1] = t_temp;
  }

  uint64_t *result = (uint64_t*)malloc(sizeof(uint64_t) * 3);
  result[0] = a;
  result[1] = s[0];
  result[2] = t[0];

  return result;
}
