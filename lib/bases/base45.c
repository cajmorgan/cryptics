#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bases.h"


/*** BASE45 LIB C ***\
  The Alphanumeric mode is defined to use 45 characters as specified in
   this alphabet.

                  Table 1: The Base45 Alphabet

   Value Encoding  Value Encoding  Value Encoding  Value Encoding
      00 0            12 C            24 O            36 Space
      01 1            13 D            25 P            37 $
      02 2            14 E            26 Q            38 %
      03 3            15 F            27 R            39 *
      04 4            16 G            28 S            40 +
      05 5            17 H            29 T            41 -
      06 6            18 I            30 U            42 .
      07 7            19 J            31 V            43 /
      08 8            20 K            32 W            44 :
      09 9            21 L            33 X
      10 A            22 M            34 Y
      11 B            23 N            35 Z
***/


int swap_table(int byte) {
  if (byte >= 0 && byte <= 9) {
    return byte + 48;
  }

  if (byte > 9 && byte < 36) {
    return byte + 55;
  }

  switch(byte) {
    case 36:
      return ' ';
    case 37:
      return '$';
    case 38:
      return '%';
    case 39:
      return '*';
    case 40:
      return '+';
    case 41:
      return '-';
    case 42:
      return '.';
    case 43:
      return '/';
    case 44:
      return ':';
    default:
      return byte;
  }

}

unsigned char swap_back_table(unsigned char byte) {
  if (byte >= 48 && byte <= 57) {
    return byte - 48;
  }

  if (byte > 64 && byte < 91) {
    return byte - 55;
  }

  switch(byte) {
    case ' ':
      return 36;
    case '$':
      return 37;
    case '%':
      return 38;
    case '*':
      return 39;
    case '+':
      return 40;
    case '-':
      return 41;
    case '.':
      return 42;
    case '/':
      return 43;
    case ':':
      return 44;
    default:
      return byte;
  }

}

/** ENCODER **/
void cryptics_bases_base45_encode(char *input) {
  int input_size = strlen(input);
  unsigned int bytes[input_size];
  int counter = 0;
  int byte_count = 0;

  while(counter < input_size) {
    unsigned int byte = 0;
    if (counter == input_size - 1)
      byte = input[counter];
    else
      byte = (input[counter] * 256) + input[counter + 1];

    bytes[byte_count++] = byte;
    counter += 2;
  }

  unsigned char remainders[byte_count][3];
  for (int i = 0; i < byte_count; i++) {
    unsigned int byte = bytes[i];
    for (int j = 0; j < 3; j++) {
      unsigned char remainder = byte % 45;
      byte = (byte - remainder) / 45;
      remainders[i][j] = remainder;
    }
  }

  int result_counter = 0;
  unsigned char *result = (unsigned char*)malloc(byte_count*3);
  if (!result) {
    printf("Malloc failed allocating memory base45 encoder");
    exit(EXIT_FAILURE);
  }

  for(int i = 0; i < byte_count; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == byte_count -1 && remainders[i][2] == 0) {
        if (remainders[i][j] == 0)
          break;
      }

      result[result_counter++] = swap_table(remainders[i][j]);
    }
  }

  input = realloc(input, result_counter);
  if (!input) {
    printf("Realloc failed allocating memory base45 encoder");
    exit(EXIT_FAILURE);
  }

  int string_cpy;
  for (string_cpy = 0; string_cpy < result_counter; string_cpy++)
    input[string_cpy] = result[string_cpy];
  input[string_cpy] = '\0';
}

/** DECODER **/
void cryptics_bases_base45_decode(char *input) {
  int input_size = strlen(input);
  int input_counter = 0;
  unsigned char remainders[input_size][3];

  for (int i = 0; i < input_size; i) {
    /** Clean out zeros**/
    for (int j = 0; j < 3; j++) {
      remainders[input_counter][j] = swap_back_table(input[i++]);
    }

    input_counter++;
  }

  unsigned int byte_sequence[input_counter];
  for (int i = 0; i < input_counter; i++) {
    unsigned int return_byte = 0;
    for (int j = 0; j < 3; j++) {
      return_byte += remainders[i][j] * pow(45, j);
    }

    byte_sequence[i] = return_byte;
  }

  int result_counter = 0;
  unsigned char result[input_size];
  for (int i = 0; i < input_counter; i++) {
    unsigned char remainder = byte_sequence[i] % 256;
    unsigned char first_to_push = (byte_sequence[i] - remainder) / 256;
    if (first_to_push != 0)
      result[result_counter++] = first_to_push;
    result[result_counter++] = remainder;
  }

  int string_cpy;
  for (string_cpy = 0; string_cpy < result_counter; string_cpy++)
    input[string_cpy] = result[string_cpy];
  input[string_cpy] = '\0';
}
