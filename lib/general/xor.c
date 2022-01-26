#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"

void cryptics_general_xor_string(char *phrase, char *key) {
  int phrase_index, key_index, key_length;
  phrase_index = key_index = 0;

  key_length = strlen(key);

  while (phrase[phrase_index] != '\0') {
    phrase[phrase_index] ^= key[key_index];
    key_index++;
    phrase_index++;

    if (key_index == key_length)
      key_index = 0;
  }
}
