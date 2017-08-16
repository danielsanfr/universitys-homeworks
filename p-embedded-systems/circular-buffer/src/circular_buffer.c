#include "circular_buffer.h"

void init_buffer(CircularBuffer *circular_buffer, uint8_t *data, int size)
{
    circular_buffer->data = data;
    circular_buffer->head = &circular_buffer->data[0];
    circular_buffer->tail = &circular_buffer->data[size - 1];
}

int push(CircularBuffer *circular_buffer, uint8_t byte)
{
    *circular_buffer->head = byte;
    if (circular_buffer->head == circular_buffer->tail) {
        return -1;
    } else {
        circular_buffer->head += sizeof(uint8_t);
        return 0;
    }
}

uint8_t pop(CircularBuffer *circular_buffer)
{
    uint8_t byte = *circular_buffer->head;
    circular_buffer->head -= sizeof(uint8_t);
    return byte;
}

