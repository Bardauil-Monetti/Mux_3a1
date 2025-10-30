#ifndef MUX_3A1_H
#define MUX_3A1_H
#include "stm32f103xb.h"
#include <stdint.h>
/*los estados de las entradas y selectoras son determinados 
por las lecturas de esas entradas (por ejemplo pulsadores)*/
typedef struct{
    GPIO_TypeDef* puerto;
    uint16_t pin;
}pinConfig_t;

typedef struct{
    pinConfig_t entradas[3];
    pinConfig_t selectoras[2];
    pinConfig_t salida;
}mux_t;

void mux_3a1_Init(mux_t*);
void mux_3a1(mux_t*);
#endif