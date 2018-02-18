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
 * File:   RingBuffer.h
 * Author: Fabvalaaah
 *
 * 02/20/2018
 */

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