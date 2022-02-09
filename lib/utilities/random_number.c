#include <sys/random.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

#define BUFFER_SIZE 16
/** Returns true random number between 0 - 1 **/
double cryptics_utilities_random_num() {
  char rand_buf[BUFFER_SIZE];
  double random_num = 1;
  int random_mod = 0;

  int stat = getrandom(rand_buf, BUFFER_SIZE, 0);
  if (stat <= 0) {
    return -1.00;
  }

  random_mod = abs(rand_buf[8]) % 12;
  if (random_mod < 6)
    random_mod += 6;

  for(int i = 0; i < random_mod; i++) {
    if (rand_buf[i] > 0)
      random_num *= abs(rand_buf[i]);
  }

  while (random_num >= 1) {
    random_num /= 10;
  }

  return random_num;
}
