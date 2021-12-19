#include "bv.h"
#include "field.h"
#include "set.h"
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "aswrvhi:n:S:"
#define DEFAULT_SEED 7566707
#define DEFAULT_SIZE 10
#define MAX_SIZE 1024

// Arrays
static void (*functions[])() = {field_touch_sequential, field_touch_wide,
                                field_touch_random};
static char *function_type[] = {"Sequential", "Wide", "Random"};

// Functions
static inline void print_help();
static inline void all_functions(uint32_t size, uint32_t max_iters,
                                 unsigned int seed);

// Enum
typedef enum { ALL, SEQUENTIAL, WIDE, RANDOM, HELP } Funcs;

static bool verbose = false;

int main(int argc, char **argv) {
  //	BitVector *bv = bv_create(50);
  //	bv_set_bit(bv, 0);
  //	bv_print(bv);

  // Initializing
  uint32_t seed = DEFAULT_SEED;
  bool custom_iters = false;
  uint32_t iters = 10;
  uint32_t size = DEFAULT_SIZE;
  Set s = 0;

  // Flags
  int opt = getopt(argc, argv, OPTIONS);

  while (opt != -1) {
    switch (opt) {
    case 'h':
      s = insert_set(HELP, s);
      break;
    case 'a':
      s = insert_set(ALL, s);
      break;
    case 'w':
      s = insert_set(WIDE, s);
      break;
    case 'r':
      s = insert_set(RANDOM, s);
      break;
    case 's':
      s = insert_set(SEQUENTIAL, s);
      break;
    case 'v':
      verbose = true;
      break;
    case 'i':
      if (optarg != NULL) {
        long temp_iters = strtol(optarg, NULL, 10);
        // Argument is invalid, meaning not an integer
        if (errno == EINVAL) {
          // The argument is another flag
          if (optarg[0] == '-') {
            optind--;
          } else { // Some invalid string
            puts("Invalid input. Setting iters size as default.");
          }
        } else if (temp_iters < 0) {
          // Argument is a value but less than 0 or greater than the unsigned
          // max
          puts("Out of range. Setting iters size as default.");
        } else {
          // Value passed is valid
          iters = temp_iters;
          custom_iters = true;
        }
      }
      break;
    case 'n':
      if (optarg != NULL) {
        long temp_size = strtol(optarg, NULL, 10);
        // Argument is invalid, meaning not an integer
        if (errno == EINVAL) {
          // The argument is another flag
          if (optarg[0] == '-') {
            optind--;
          } else { // Some invalid string
            puts("Invalid input. Setting size as default.");
          }
        } else if (temp_size > MAX_SIZE || temp_size < 1) {
          // Argument is a value but less than 0 or greater than the unsigned
          // max
          puts("Out of range. Setting size as default.");
        } else {
          // Value passed is valid
          size = temp_size;
        }
      }
      break;
    case 'S':
      if (optarg != NULL) {
        long temp_seed = strtol(optarg, NULL, 10);

        // Argument is invalid, meaning not an integer
        if (errno == EINVAL) {
          // The argument is another flag
          if (optarg[0] == '-') {
            optind--;
          } else { // Some invalid string
            puts("Invalid input. Setting seed size as default.");
          }
        } else if (temp_seed < 0) {
          // Argument is a value but less than 0 or greater than the unsigned
          // max
          puts("Out of range. Setting seed size as default.");
        } else {
          // Value passed is valid
          seed = temp_seed;
        }
      }
      break;
    }

    opt = getopt(argc, argv, OPTIONS);
  }

  // If iters was not declared by user, then
  // iters is size * size
  if (!custom_iters) {
    iters = size * size;
  } else if (iters > (size * size)) {
    // Iters cannot be greater than size * size as it can break the program
    printf("Iters cannot be greater than the size squared. Setting iters to be "
           "default.\n");
    iters = size * size;
  }

  // A hierarchy of functions
  if (member_set(HELP, s)) {
    print_help();
    return 0;
  } else if (member_set(ALL, s)) {
    all_functions(size, iters, seed);
  } else {
    // Loops through the Funcs enum starting from SEQUENTIAL
    // Ending at RANDOM
    for (Funcs fn = ALL + 1; fn < HELP; fn += 1) {
      if (member_set(fn, s)) {
        Field *f = field_create(size);

        functions[fn - 1](f, iters, seed);
        field_print(f);

        if (verbose) {
          uint32_t touched = field_count(f);
          uint32_t writes = field_writes(f);

          printf("%s:\n", function_type[fn - 1]);
          printf("\t%20s%" PRIu32 "\n", function_type[fn - 1], touched);
          printf("\t%20s%" PRIu32 "\n", function_type[fn - 1], writes);
          printf("\t%20s%f%%\n", function_type[fn - 1],
                 100 * ((double)writes / (double)touched));
        }
        field_delete(&f);
      }
    }
  }

  return 0;
}

void print_help() {
  printf("SYNOPSIS\n\tCompare different methods of touching grass.\n\n");
  printf("USAGE\n\t./grass [-aswrvh] [-f size] [-n seed]\n\n");
  printf("OPTIONS\n");
  return;
}

void all_functions(uint32_t size, uint32_t max_iters, unsigned int seed) {
  for (int i = 0; i < 3; i++) {
    Field *f = field_create(size);
    printf("%s:\n", function_type[i]);
    functions[i](f, max_iters, seed);

    if (verbose) {
      uint32_t count = field_count(f);
      uint32_t writes = field_writes(f);
	  double efficiency = 100 * count / writes;

      printf("\t%20s%" PRIu32 "\n", "Touched blades:", count);
      printf("\t%20s%" PRIu32 "\n", "BitVector writes:", writes);
      printf("\t%20s%f%%\n",
             "Efficiency:", efficiency);
    } else {
      // Prints field when verbose is not declared
      field_print(f);
    }
    field_delete(&f);
  }
  return;
}
