#include "field.h"
#include "bv.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Ben's field.c to fix wide
#define MIN(x, y) ((x < y) ? x : y)

typedef struct Field {
  uint32_t size;
  BitVector *matrix;
} Field;

Field *field_create(uint32_t size) {
  Field *field = malloc(sizeof(Field));

  if (field != NULL) {
    field->size = size;
    field->matrix = bv_create(size * size);

    if (field->matrix == NULL) {
      free(field);
      field = NULL;
    }
  }

  return field;
}

void field_delete(Field **f) {
  if (f) {
    bv_delete(&(*f)->matrix);
    free(*f);
    f = NULL;
  }

  return;
}

uint32_t field_size(Field *f) { return f->size; }

uint32_t field_area(Field *f) { return f->size * f->size; }

uint32_t field_count(Field *f) {
  if (f) {
    uint32_t count = 0;

    // For Matrix count
    for (uint32_t i = 0; i < field_area(f); i += 1) {
      bool temp_b = false;

      if (bv_get_bit(f->matrix, i, &temp_b) && temp_b) {
        count += 1;
      }
    }

    return count;
  }

  return 0;
}

uint32_t field_writes(Field *f) {
  if (f != NULL) {
    return bv_writes(f->matrix);
  }

  return 0;
}

void field_touch_sequential(Field *f, uint32_t max_iters, unsigned int seed) {
  (void)seed;

  if (f != NULL) {
    for (uint32_t i = 0; i < max_iters; i += 1) {
      bv_set_bit(f->matrix, i);
    }

    return;
  }

  return;
}

void field_touch_wide(Field *f, uint32_t max_iters, unsigned int seed) {
  (void)seed;

  // Ben.c - field.c to fix this function
  uint32_t area = field_area(f),
		   necessary_iters = area % 64 == 0 ? (area / 64) : (area / 64 + 1),
		   end = MIN(max_iters, necessary_iters);

  if (f != NULL) {
    for (uint32_t i = 0; i < end; i += 1) {
      bv_set_64(f->matrix, i*64);
    }
  }

  return;
}

void field_touch_random(Field *f, uint32_t max_iters, unsigned int seed) {
  if (f != NULL) {
    // Sets the random seed
    srandom(seed);
    for (uint32_t i = 0; i < max_iters; i += 1) {
      bv_set_bit(f->matrix, random() % field_area(f));
    }
  }

  return;
}

void field_print(Field *f) {
  for (uint32_t i = 0; i < f->size; i += 1) {
    for (uint32_t x = 0; x < f->size; x += 1) {
      bool curr_bit = false;
      uint32_t index = i * f->size + x;
      bv_get_bit(f->matrix, index, &curr_bit);
      printf("%s", (curr_bit) ? "_" : "/");
    }
    printf("\n");
  }
}
