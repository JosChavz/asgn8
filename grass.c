#include "bv.h"
#include "field.h"
#include "set.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OPTIONS "aSwrvhi:n:s:"
#define SEED 756670
#define SIZE 10
#define MAX_SIZE 1024

static inline void print_help();
typedef enum {
  ALL,
  SEQUENTIAL,
  WIDE,
  RANDOM,
  HELP
} static bool verbose = false;

int main(void) {
  // Initializing
  uint32_t seed = 7566707;
  uint32_t iters = 10;
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
          iters = 25;
        } else {
          // Value passed is valid
	  iters = temp_iters * temp_iters;
        }
      }
      break;
    case 'n':
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
          iters = 25;
        } else {
          // Value passed is valid
	  iters = temp_iters * temp_iters;
        }
      }
      break;
    case 'S':
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
          iters = 25;
        } else {
          // Value passed is valid
	  iters = temp_iters * temp_iters;
        }
      }
      break;
    }

    opt = getopt(argc, argv, OPTIONS);
  }

  return 0;
}
