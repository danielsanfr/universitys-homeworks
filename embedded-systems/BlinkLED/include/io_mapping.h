#include <stdint.h>

#define PIN_13 ((uint16_t) 0x2000)  // PIN 13 selected

#define PERIPH_BASE ((uint32_t) 0x40000000) // Peripheral base address in the alias region

#define APB2PERIPH_BASE (PERIPH_BASE + 0x10000)

#define GPIOC_BASE (APB2PERIPH_BASE + 0x1000)

#define GPIOC ((GPIO *) GPIOC_BASE)

#define __IO volatile // Defines 'read / write' permissions

typedef struct
{
  __IO uint32_t CRL;
  __IO uint32_t CRH;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  __IO uint32_t BSR;
  __IO uint32_t BRR;
  __IO uint32_t LCK;

} GPIO;

