#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

  #include <stdint.h>
  void cryptics_general_xor_string(char *, char *);
  uint64_t cryptics_general_lcm(uint64_t, uint64_t);
  uint64_t cryptics_general_gcd(uint64_t, uint64_t);
  int64_t *cryptics_general_gcd_extended(uint64_t, uint64_t);
  uint64_t cryptics_general_mod(int64_t a, int64_t m);

#endif // GENERAL_H_INCLUDED
