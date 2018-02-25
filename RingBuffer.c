/*
 * MIT License
 * 
 * Copyright (c) 2018 Fabvalaaah - fabvalaaah@laposte.net
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * DONATION:
 * As I share these sources for commercial use too, maybe you could consider
 * sending me a reward (even a tiny one) to my Ethereum wallet at the address
 * 0x1fEaa1E88203cc13ffE9BAe434385350bBf10868
 * If so, I would be forever grateful to you and motivated to keep up the good
 * work for sure :oD Thanks in advance !
 * 
 * FEEDBACK:
 * You like my work? It helps you? You plan to use/reuse/transform it? You have
 * suggestions or questions about it? Just want to say "hi"? Let me know your
 * feedbacks by mail to the address fabvalaaah@laposte.net
 * 
 * DISCLAIMER:
 * I am not responsible in any way of any consequence of the usage
 * of this piece of software. You are warned, use it at your own risks.
 */

/* 
 * File:   RingBuffer.c
 * Author: Fabvalaaah
 *
 * 02/20/2018
 */

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
 * Frees the memory allocated to a ring buffer (the pointer is then set to
 * NULL).
 */
void destroyRingBuffer(_RingBuffer** buffer) {
    if (!buffer || !(*buffer)) {
        return;
    }

    if ((*buffer)->begin) {
        free((*buffer)->begin);
    }

    free(*buffer);
    *buffer = NULL;
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
 * Removes n bytes from a ring buffer, 0 <= n < buffer->size.
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