#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "circular_buffer.h"

#define millis(x) x * 1000
#define second(x) 1000 * millis(x)

#define DATA_SIZE 80

int main (int argc, char *argv[])
{
    uint8_t data[DATA_SIZE];
    CircularBuffer circular_buffer;
    init_buffer(&circular_buffer, data, DATA_SIZE);

    srand(time(NULL));
    while (1) {
        int error = push(&circular_buffer, rand());
        // printf("Byte: %x\n", *(circular_buffer.head - 1));
        
        if (error) {
            int int_data[20];
            memcpy(int_data, circular_buffer.data, DATA_SIZE);
			printf("Integers: %d", int_data[0]);
			for (int i = 1; i < 20; i++) {
				printf(", %d", int_data[i]);
			}
			printf("\n");
            break;
        }
        
        usleep(millis(200));
    }

    return 0;
}

