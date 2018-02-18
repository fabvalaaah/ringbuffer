#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RingBuffer.h"

/*
 * Creates a ring buffer of a specified size.
 * Returns a pointer to this buffer.
 * Returns NULL on memory allocation error.
 */
_RingBuffer* createRingBuffer(uint32_t size) {
    _RingBuffer* buffer = malloc(sizeof (_RingBuffer));
    memset(buffer, '\0', sizeof (_RingBuffer));

    if (!buffer || !size) {
        return NULL;
    }

    buffer->begin = calloc(size, sizeof (uint8_t));
    if (!(buffer->begin)) {
        free(buffer);
        return NULL;
    }
    buffer->end = buffer->begin + size - 1;
    buffer->head = buffer->begin;
    buffer->tail = buffer->begin;

    return buffer;
}

/*
 * Free the memory allocated to a ring buffer (the pointer is then set to NULL).
 */
void destroyRingBuffer(_RingBuffer** buffer) {
    if (!buffer || !(*buffer)) {
        return;
    }

    if ((*buffer)->begin) {
        free((*buffer)->begin);
    }

    free(*buffer);
    buffer = NULL;
}

/*
 * Prints the content of a ring buffer.
 */
void printRingBuffer(_RingBuffer* buffer) {
    uint8_t* ptr;

    if (!buffer) {
        fprintf(stdout, "[]");
    }

    fprintf(stdout, "[");
    ptr = buffer->begin;
    while (ptr <= buffer->end) {
        fprintf(stdout, "|%u|", *ptr);
        ptr++;
    }
    fprintf(stdout, "]\n");
}

/*
 * Static tool method.
 * Calculates the next position of the pointer considering the buffer as toric.
 */
static void nextPos(_RingBuffer* buffer, uint8_t** pos) {
    if (!buffer || !pos || !(*pos)) {
        return;
    }

    if (*pos == buffer->end) {
        *pos = buffer->begin;
    } else {
        (*pos)++;
    }
}

/*
 * Static tool method.
 * Calculates the next position of the tail pointer and pushes the head pointer
 * forward along the buffer when colliding.
 */
static void nextTailPos(_RingBuffer* buffer) {
    if (!buffer) {
        return;
    }

    nextPos(buffer, &(buffer->tail));

    if (buffer->size && buffer->tail == buffer->head) {
        nextPos(buffer, &(buffer->head));
    }
}

/*
 * Adds a byte to the tail.
 * Returns the new "size" i.e. the amount of data stored into the ring buffer.
 * Returns 0 on null buffer.
 */
uint32_t addToRingBuffer(_RingBuffer* buffer, uint8_t value) {
    if (!buffer) {
        return 0;
    }

    if (buffer->size) {
        nextTailPos(buffer);
    }

    *(buffer->tail) = value;
    if (buffer->size < buffer->end - buffer->begin + 1) {
        buffer->size++;
    }

    return buffer->size;
}

/*
 * Returns the byte at the head (no removal).
 * Returns '\0' on null buffer.
 */
uint8_t peekFromRingBuffer(_RingBuffer* buffer) {
    if (!buffer) {
        return '\0'; /* Arbitrary value */
    }

    return *(buffer->head);
}

/*
 * Removes the byte from the head.
 * Returns the removed byte.
 * Returns '\0' on null buffer.
 */
uint8_t removeFromRingBuffer(_RingBuffer* buffer) {
    uint8_t value;

    if (!buffer || !(buffer->size)) {
        return '\0'; /* Arbitrary value */
    }

    value = *(buffer->head);
    *(buffer->head) = '\0';
    (buffer->size)--;
    if (buffer->size) {
        nextPos(buffer, &(buffer->head));
    }

    return value;
}

/*
 * Returns n bytes from a ring buffer (no removal). If n exceeds the size of the
 * buffer, it considers the buffer as toric.
 * The bytes are stored in a pre-allocated array "data".
 */
void nPeekFromRingBuffer(_RingBuffer* buffer, uint8_t* data, uint32_t n) {
    uint32_t total, delta, occ, mod;
    uint8_t* ptr;

    if (!buffer || !data) {
        return;
    }

    total = buffer->end - buffer->begin + 1;
    delta = buffer->end - buffer->head + 1;
    if (n <= delta) {
        memcpy(data, buffer->head, n);
    } else {
        occ = (n - delta) / total;
        mod = (n - delta) % total;
        memcpy(data, buffer->head, delta);
        ptr = data + delta;
        while (occ) {
            memcpy(ptr, buffer->begin, total);
            ptr += total;
            occ--;
        }
        memcpy(ptr, buffer->begin, mod);
    }
}

/*
 * Removes n bytes from a ring buffer, n <= 0 <= buffer->size.
 * The bytes are stored in a pre-allocated array "data".
 * Returns the number of bytes that have been removed.
 */
uint32_t nRemoveFromRingBuffer(_RingBuffer* buffer, uint8_t* data, uint32_t n) {
    uint32_t i, count = 0;
    uint8_t* ptr = NULL;

    if (!buffer || !data) {
        return 0;
    }

    if (n < buffer->size) {
        count = n;
    } else {
        count = buffer->size;
    }

    ptr = data;
    for (i = 0; i < count; i++) {
        if (ptr) {
            *ptr = removeFromRingBuffer(buffer);
            ptr++;
        }
    }

    return count;
}