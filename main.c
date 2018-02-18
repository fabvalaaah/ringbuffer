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
 * File:   main.c
 * Author: Fabvalaaah
 *
 * 02/20/2018
 */

#include <stdio.h>
#include <string.h>
#include "RingBuffer.h"

#define RING_BUFFER_DEFAULT_SIZE 5

void main() {
    _RingBuffer* buffer = createRingBuffer(RING_BUFFER_DEFAULT_SIZE);
    uint8_t tab1[11], tab2[4];
    uint32_t i;

    fprintf(stdout, "BUFFER CREATION\n");
    addToRingBuffer(buffer, 1);
    addToRingBuffer(buffer, 2);
    addToRingBuffer(buffer, 3);
    addToRingBuffer(buffer, 4);
    addToRingBuffer(buffer, 5);
    addToRingBuffer(buffer, 6);
    printRingBuffer(buffer);
    fprintf(stdout, "-------\n");

    fprintf(stdout, "REMOVE: %u\n", removeFromRingBuffer(buffer));
    printRingBuffer(buffer);
    fprintf(stdout, "-------\n");

    fprintf(stdout, "PEEK 11 values: ");
    nPeekFromRingBuffer(buffer, tab1, 11);
    for (i = 0; i < 11; i++) {
        fprintf(stdout, "-%u-", tab1[i]);
    }
    fprintf(stdout, "\n");

    fprintf(stdout, "ADD 7\n");
    addToRingBuffer(buffer, 7);
    printRingBuffer(buffer);
    fprintf(stdout, "-------\n");

    fprintf(stdout, "REMOVE: %u\n", removeFromRingBuffer(buffer));
    printRingBuffer(buffer);
    fprintf(stdout, "-------\n");

    fprintf(stdout, "PEEK: -%u-\n", peekFromRingBuffer(buffer));

    fprintf(stdout, "REMOVE %u values: ", nRemoveFromRingBuffer(buffer, tab2,
            11));
    for (i = 0; i < 4; i++) {
        fprintf(stdout, "-%u-", tab2[i]);
    }
    fprintf(stdout, "\n");
    printRingBuffer(buffer);
    fprintf(stdout, "-------\n");
    memset(tab2, '\0', 4);

    fprintf(stdout, "ADD 8, 9\n");
    addToRingBuffer(buffer, 8);
    addToRingBuffer(buffer, 9);
    printRingBuffer(buffer);
    fprintf(stdout, "-------\n");


    fprintf(stdout, "REMOVE: %u\n", removeFromRingBuffer(buffer));
    fprintf(stdout, "REMOVE : %u\n", removeFromRingBuffer(buffer));
    printRingBuffer(buffer);
    fprintf(stdout, "-------\n");

    fprintf(stdout, "ADD 10, 11, 12, 13\n");
    addToRingBuffer(buffer, 10);
    addToRingBuffer(buffer, 11);
    addToRingBuffer(buffer, 12);
    addToRingBuffer(buffer, 13);
    printRingBuffer(buffer);
    fprintf(stdout, "-------\n");


    fprintf(stdout, "REMOVE: %u\n", removeFromRingBuffer(buffer));
    fprintf(stdout, "REMOVE: %u\n", removeFromRingBuffer(buffer));
    fprintf(stdout, "REMOVE: %u\n", removeFromRingBuffer(buffer));
    printRingBuffer(buffer);
    fprintf(stdout, "-------\n");

    fprintf(stdout, "REMOVE: %u\n", removeFromRingBuffer(buffer));
    fprintf(stdout, "REMOVE: %u\n", removeFromRingBuffer(buffer));
    printRingBuffer(buffer);
    fprintf(stdout, "-------\n");

    fprintf(stdout, "REMOVE %u values: ", nRemoveFromRingBuffer(buffer, tab2,
            4));
    for (i = 0; i < 4; i++) {
        fprintf(stdout, "-%u-", tab2[i]);
    }
    fprintf(stdout, "\n");
    printRingBuffer(buffer);
    fprintf(stdout, "-------\n");

    destroyRingBuffer(&buffer);
}