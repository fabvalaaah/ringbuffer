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