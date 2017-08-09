#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>

typedef struct {
    uint8_t *data;
    uint8_t *head;
    uint8_t *tail;
} CircularBuffer; 

void init_buffer(CircularBuffer *circular_buffer, uint8_t *data, int size);

int push(CircularBuffer *circular_buffer, uint8_t byte);

uint8_t pop(CircularBuffer *circular_buffer);

#endif // CIRCULAR_BUFFER_H

