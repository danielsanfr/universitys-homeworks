#include "io_mapping.h"

#define CLK 720 // Clock em MHz

#define delay(milliseconds) for (int i = 0; i < milliseconds * CLK; i++) { }

#define IOWRITE(GPIO_X, PIN_X, VALUE); ((GPIO *) GPIO_X)->ODR ^= (-VALUE ^ ((GPIO *) GPIO_X)->ODR) & (1 << PIN_X);

#define IOSET(GPIO_X, PIN_X); ((GPIO *) GPIO_X)->ODR |= 1 << PIN_X;

#define IOCLEAR(GPIO_X, PIN_X); ((GPIO *) GPIO_X)->ODR &= ~(1 << PIN_X);

#define IOTOGGLE(GPIO_X, PIN_X); ((GPIO *) GPIO_X)->ODR ^= 1 << PIN_X;

