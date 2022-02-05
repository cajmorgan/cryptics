#include <sys/random.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

#define BUFFER_SIZE 256
/** Returns true random number between 0 - 1 **/
double cryptics_utilities_random_num() {
  char rand_buf[BUFFER_SIZE];
  double random_num = 1;

  int stat = getrandom(rand_buf, BUFFER_SIZE, 0);
  if (stat <= 0) {
    return -1;
  }

  for(int i = 0; i < 9; i++) {
    random_num *= abs(rand_buf[i]);
  }

  while (random_num >= 1) {
    random_num /= 10;
  }

  return random_num;
}
