#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdint.h>

typedef struct RingBuffer {
    uint8_t* begin;
    uint8_t* end;
    uint8_t* head;
    uint8_t* tail;
    uint32_t size;
} _RingBuffer;

_RingBuffer* createRingBuffer(uint32_t size);
void destroyRingBuffer(_RingBuffer** buffer);
void printRingBuffer(_RingBuffer* buffer);
uint32_t addToRingBuffer(_RingBuffer* buffer, uint8_t value);
uint8_t peekFromRingBuffer(_RingBuffer* buffer);
void nPeekFromRingBuffer(_RingBuffer* buffer, uint8_t* data, uint32_t n);
uint8_t removeFromRingBuffer(_RingBuffer* buffer);
uint32_t nRemoveFromRingBuffer(_RingBuffer* buffer, uint8_t* data, uint32_t n);

#endif /* RINGBUFFER_H */