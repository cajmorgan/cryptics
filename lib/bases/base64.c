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
         0 A            17 R            34 i            51 z
         1 B            18 S            35 j            52 0
         2 C            19 T            36 k            53 1
         3 D            20 U            37 l            54 2
         4 E            21 V            38 m            55 3
         5 F            22 W            39 n            56 4
         6 G            23 X            40 o            57 5
         7 H            24 Y            41 p            58 6
         8 I            25 Z            42 q            59 7
         9 J            26 a            43 r            60 8
        10 K            27 b            44 s            61 9
        11 L            28 c            45 t            62 +
        12 M            29 d            46 u            63 /
        13 N            30 e            47 v
        14 O            31 f            48 w            64 =
        15 P            32 g            49 x
        16 Q            33 h            50 y
***/


#define SEXTET 63
#define OCTET 255
/** Encoding **/
#define NO_PADDING 3
#define ONE_PADDING 2
#define TWO_PADDING 1
/** Decoding **/
#define NO_PADDING_REV 4
#define ONE_PADDING_REV 3
#define TWO_PADDING_REV 2

unsigned char swap_table(int byte) {
  char return_char;
  if (byte >= 0 && byte <= 25) {
    return_char = byte + 65;
    return return_char;
  }

  if (byte >= 26 && byte <= 51) {
    return_char = byte + 71;
    return return_char;
  }

  if (byte >= 52 && byte <= 61) {
    return_char = byte - 4;
    return return_char;
  }

  switch(byte) {
    case 62: {
      return_char = byte - 19;
      return return_char;
    } case 63: {
      return_char = byte - 16;
      return return_char;
    } case 64: {
      return_char = byte - 3;
      return return_char;
    } default: {
      return byte;
    }

  }

}

int swap_back_table(int byte) {
  char return_char;

  if (byte >= 48 && byte <= 57) {
    return_char = byte + 4;
    return return_char;
  }

  if (byte >= 65 && byte <= 90) {
    return_char = byte - 65;
    return return_char;
  }

  if (byte >= 97 && byte <= 122) {
    return_char = byte - 71;
    return return_char;
  }

  switch(byte) {
    case 43: {
      return_char = byte + 19;
      return return_char;
    } case 47: {
      return_char = byte + 16;
      return return_char;
    } case 61: {
      return_char = byte + 3;
      return return_char;
    } default: {
      return byte;
    }
  }

}

void cryptics_bases_base64_encode(char *input) {
  int first_group_length = 0;
  int input_length = strlen(input);
  unsigned int first_group_bytes[input_length][3];
  int group_sizes[input_length*3];
  for (int i = 0; i < input_length*3; i++)
    group_sizes[i] = 0;

  for (int i = 0; i < input_length; i) {
    while(group_sizes[first_group_length] != 3 && input[i]) {
      first_group_bytes[first_group_length][group_sizes[first_group_length]] = input[i++];
      group_sizes[first_group_length]++;
    }

    first_group_length++;
  }


  int second_group_bits[first_group_length][4];

  for (int i = 0; i < first_group_length; i++) {
    unsigned int joined = 0;
    int number_of_octets = group_sizes[i];

    for (int j = 0; j < number_of_octets; j++) {
      joined |= first_group_bytes[i][j];

      if (j != number_of_octets - 1)
        joined = joined << 8;
    }

    int second_index = 0;
    switch(number_of_octets) {
      case NO_PADDING: {
        for (int step = NO_PADDING; step >= 0; step--) {
          int first = (joined >> (step*6)) & SEXTET;
          second_group_bits[i][second_index++] = first;
        }

        break;
      } case ONE_PADDING: {
        int first = joined >> 10 & SEXTET;
        int second = joined >> 4 & SEXTET;
        int third = joined << 2 & SEXTET;
        second_group_bits[i][0] = first;
        second_group_bits[i][1] = second;
        second_group_bits[i][2] = third;
        second_group_bits[i][3] = 64;

        break;
      } case TWO_PADDING: {
        int first = joined >> 2 & SEXTET;
        int second = joined << 4 & SEXTET;
        second_group_bits[i][0] = first;
        second_group_bits[i][1] = second;
        second_group_bits[i][2] = 64;
        second_group_bits[i][3] = 64;

        break;
      }

      default:
        break;
    }
  }

  int counter = 0;
  unsigned char encoded_string[first_group_length*4];
  for (int i = 0; i < first_group_length; i++) {
    for (int j = 0; j < 4; j++) {
      encoded_string[counter] = swap_table(second_group_bits[i][j]);
      counter++;
    }
  }

  encoded_string[counter] = '\0';
  input = realloc(input, counter);

  for (int i = 0; i < counter; i++) {
    input[i] = encoded_string[i];
  }
}

void cryptics_bases_base64_decode(char *input) {
  int input_length = strlen(input);
  int group_return_bytes[input_length][4];
  int swap_back_counter = 0;
  int group_sizes[input_length*4];
  for (int i = 0; i < input_length*4; i++)
    group_sizes[i] = 0;

  for (int i = 0; i < input_length; i) {
    while(group_sizes[swap_back_counter] != 4 && input[i]) {
      int swap_back_data = swap_back_table(input[i]);
      if (swap_back_data != 64)
        group_return_bytes[swap_back_counter][group_sizes[swap_back_counter]++] = swap_back_data;

      i++;
    }

    swap_back_counter++;
  }

  unsigned char group_return_octets[swap_back_counter][3];
  int group_return_counter[swap_back_counter*3];

  for (int i = 0; i < swap_back_counter*3; i++)
    group_return_counter[i] = 0;

  for (int i = 0; i < swap_back_counter; i++) {
    unsigned int joined = 0;
    int number_of_sextets = group_sizes[i];
    for (int j = 0; j < number_of_sextets; j++) {
      joined |= group_return_bytes[i][j];

      if (j != number_of_sextets-1)
        joined = joined << 6;

    }

    int second_index = 0;
    switch(number_of_sextets) {
      case NO_PADDING_REV: {
        for (int step = number_of_sextets/2; step >= 0; step--) {
          unsigned char first = (joined >> (8*step)) & OCTET;
          group_return_octets[i][second_index++] = first;
          group_return_counter[i]++;
        }

        break;
      } case ONE_PADDING_REV: {
        unsigned char first = (joined >> 10) & OCTET;
        unsigned char second = (joined >> 2) & OCTET;
        group_return_octets[i][0] = first;
        group_return_octets[i][1] = second;
        group_return_counter[i] += 2;
        break;

      } case TWO_PADDING_REV: {
        unsigned char first = (joined >> 4) & OCTET;
        group_return_octets[i][0] = first;
        group_return_counter[i] += 1;
        break;
      }
    }
  }

  int counter = 0;
  unsigned char decoded_string[swap_back_counter*3];
  for (int i = 0; i < swap_back_counter; i++) {
    for (int j = 0; j < group_return_counter[i]; j++) {
      decoded_string[counter] = group_return_octets[i][j];
      counter++;
    }
  }

  for (int i = 0; i < counter; i++)
    input[i] = decoded_string[i];

  input[counter] = '\0';
}
