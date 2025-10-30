#include "Mux_3a1.h"
#include "stm32f103xb.h"
#include <stdint.h>
int main (void){
    mux_t mux1;
    for(int i = 0; i < 3; i++){
        mux1.entradas[i].puerto = GPIOA;
        mux1.entradas[i].pin = i + 1;
    }
    for(int i = 0; i < 2; i++){
        mux1.selectoras[0].puerto = GPIOB;
        mux1.selectoras[0].pin = 8 + i;
    }
    mux1.salida.puerto = GPIOC;
    mux1.salida.pin = 13;
    mux_3a1_Init(&mux1);
    while(1){
        mux_3a1(&mux1);
    }
}