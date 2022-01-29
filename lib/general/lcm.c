#include <stdio.h>
#include <stdint.h>
#include "general.h"
/** Lowest common multiple, gets by a*b/gcd(a,b)**/

uint64_t cryptics_general_lcm(uint64_t a, uint64_t b) {
  int gcd = cryptics_general_gcd(a, b);
  int lcm = (a / gcd) * b;

  return lcm;
}
