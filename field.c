#include "bv.h"
#include "field.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Field {
	uint32_t size;
	BitVector *matrix;
} Field;

Field *field_create(uint32_t size) {
	Field *field = malloc(sizeof(Field));

	if (field != NULL) {
        field->size = size;
        field->matrix = (BitVector *)  bv_create(size * size);

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

uint32_t field_size(Field *f) {
	return f->size;
}

uint32_t field_area(Field *f) {
	return f->size * f->size;
}

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

uint32_t field_writes(Field *f);

void field_touch_sequential(Field *f, uint32_t max_iters, unsigned int seed);

void field_touch_wide(Field *f, uint32_t max_iters, unsigned int seed);

void field_touch_random(Field *f, uint32_t max_iters, unsigned int seed);

void field_print(Field *f);
