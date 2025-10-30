#include "Mux_3a1.h"
#include "stm32f103xb.h"
#include <stdint.h>
void mux3a1_Init(mux_t* mux){
    for(int i = 0; i < 3; i++){
        if(mux->entradas[i].pin <= 7){
            mux->entradas[i].puerto->CRL &= ~(0xF << (mux->entradas[i].pin * 4));
            mux->entradas[i].puerto->CRL |= (0x4 << (mux->entradas[i].pin * 4));
        }else{
            mux->entradas[i].puerto->CRH &= ~(0xF << ((mux->entradas[i].pin % 8) * 4));
            mux->entradas[i].puerto->CRH |= (0x4 << ((mux->entradas[i].pin % 8) * 4));
        }
    }
    for(int i = 0; i < 2; i++){
        if(mux->selectoras[i].pin <= 7){
            mux->selectoras[i].puerto->CRL &= ~(0xF << (mux->selectoras[i].pin * 4));
            mux->selectoras[i].puerto->CRL |= (0x4 << (mux->selectoras[i].pin * 4));
        }else{
            mux->selectoras[i].puerto->CRH &= ~(0xF << ((mux->selectoras[i].pin % 8) * 4));
            mux->selectoras[i].puerto->CRH |= (0x4 << ((mux->selectoras[i].pin % 8) * 4));
        }
    }
    if(mux->salida.pin <= 7){
        mux->salida.puerto->CRL &= ~(0xF << (mux->salida.pin * 4));
        mux->salida.puerto->CRL |= (0x2 << (mux->salida.pin * 4));
    }else{
        mux->salida.puerto->CRH &= ~(0xF << ((mux->salida.pin % 8) * 4));
        mux->salida.puerto->CRH |= (0x2 << ((mux->salida.pin % 8) * 4));
    }
}
void mux3a1(mux_t* mux){
    int MSB, LSB;
    MSB = mux->selectoras[0].puerto->IDR & (1 << mux->selectoras[0].pin);
    LSB = mux->selectoras[1].puerto->IDR & (1 << mux->selectoras[1].pin);
    if(!MSB && !LSB){
        if(mux->entradas[0].puerto->IDR & (1 << mux->entradas[0].pin)){
            mux->salida.puerto->BSRR |= (1 << mux->salida.pin);
        }else{
            mux->salida.puerto->BSRR |= (1 << (mux->salida.pin + 16));
        }
    }else if (!MSB && LSB){
        if(mux->entradas[1].puerto->IDR & (1 << mux->entradas[1].pin)){
            mux->salida.puerto->BSRR |= (1 << mux->salida.pin);
        }else{
            mux->salida.puerto->BSRR |= (1 << (mux->salida.pin + 16));
        }
    }else if (MSB && !LSB){
        if(mux->entradas[2].puerto->IDR & (1 << mux->entradas[2].pin)){
            mux->salida.puerto->BSRR |= (1 << mux->salida.pin);
        }else{
            mux->salida.puerto->BSRR |= (1 << (mux->salida.pin + 16));
        }
    }
}