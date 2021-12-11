#include "bv.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BitVector {
	uint32_t length;
	uint64_t *vector;
	uint32_t writes;
} BitVector;

BitVector *bv_create(uint32_t size) {
	// Alocate memory for bv variables
	BitVector *bv = (BitVector *) malloc(sizeof(BitVector));

	if (bv != NULL) {
		bv->length = 0;
		bv->writes = 0;
		// Allocate memory for vector
		// n x n BITS in vector, thus allocation is size / 64
		// to know exactly the length of the vector
		bv->vector = (uint64_t *) calloc(size / 64, sizeof(uint64_t));

		if(bv->vector == NULL) {
			// Unable to allocate memory
			free(bv);
			bv = NULL;
		}
	}

	return bv;
}

void bv_delete(BitVector **bv) {
	// Delete bv
	if(bv != NULL) {
		free((*bv)->vector);
		free(*bv);
		*bv = NULL;
	}

	return;
}

uint32_t bv_length(BitVector *bv) {
	return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
	bv->writes += 1;
	if (bv && i < bv->length) {
		bv->vector[i/64] |= (uint64_t) 0x1 << i % 64;
		return true;
	}

	return false;
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
	bv->writes += 1;
	if (bv && i < bv->length) {
		bv->vector[i / 64] &= ~((uint64_t) 0x1 << (i % 64));
	}

	return false;
}

bool bv_get_bit(BitVector *bv, uint32_t i, bool *bit) {
	if (bv && i < bv->length) {
		// Firstly grabs the bit that resides in i-position
		// Then moves that bit to the LSB
        uint64_t curr_bit = (bv->vector[i / 64] & (uint64_t) 0x1 << i % 64) >> i % 64;
		*bit = curr_bit;

		return true;
	}

	return false;
}

bool bv_set_64(BitVector *bv, uint32_t i) {
	bv->writes += 1;
	if (bv && i < bv->length) {
		bv->vector[i/64] |= ~((uint64_t) 0);
        return true;
	}

	return false;
}

bool bv_clr_64(BitVector *bv, uint32_t i) {
	bv->writes += 1;
	if (bv->vector) {
		bv->vector[i / 64] &= (uint64_t) 0;
	}

	return false;
}

uint32_t bv_writes(BitVector *bv) {
	if (bv) {
		return bv->writes;
	}

	return 0;
}

void bv_print(BitVector *bv) {
    printf("%c ", '[');
    for (uint32_t i = 0; i < bv->length; i++) {
		bool temp_b = false;
        bool c_bit = bv_get_bit(bv, i, &temp_b);
        printf("%d ", c_bit);
    }
    printf("%c\n", ']');
}

