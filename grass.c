#include "bv.h"
#include "field.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OPTIONS "aswrvhi:n:s:"

int main(void) {
  // Flags
  int opt = getopt(argc, argv, OPTIONS);

  while (opt != -1) {
	  switch(opt) {
		  case 'h':
			  print_help();
			  return 0;
		case 'a':
			  //tbd
	  }

	  opt = getopt(argc, argv, OPTIONS);
  }

  return 0;
}
