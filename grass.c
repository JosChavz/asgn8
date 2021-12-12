#include "bv.h"
#include "field.h"
#include "set.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define OPTIONS "aSwrvhi:n:s:"
#define DEFAULT_SEED 756670
#define DEFAULT_SIZE 10
#define MAX_SIZE 1024

static inline void print_help();
typedef enum {
  ALL,
  SEQUENTIAL,
  WIDE,
  RANDOM,
  HELP
} static bool verbose = false;

int main(int argc, char **argv) {
  // Initializing
  uint32_t seed = DEFAULT_SEED;
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
        } else if (temp_iters > UINT_MAX || temp_iters < 0) {
          // Argument is a value but less than 0 or greater than the unsigned
          // max
          puts("Out of range. Setting iters size as default.");
        } else {
          // Value passed is valid
	  iters = temp_iters * temp_iters;
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
        } else if (temp_seed > UINT_MAX || temp_seed < 0) {
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

  return 0;
}
