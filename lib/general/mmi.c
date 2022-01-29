#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../cryptics.h"


/** Modular Multiplicative Inverse **/
uint64_t cryptics_general_mmi(uint64_t a, uint64_t m) {
  int64_t *gcd_ext = cryptics_general_gcd_extended(a, m);

  if(gcd_ext[0] != 1) {
    return -1;
  }

  uint64_t res = cryptics_general_mod(gcd_ext[1], m);
  free(gcd_ext);

  return res;
}
