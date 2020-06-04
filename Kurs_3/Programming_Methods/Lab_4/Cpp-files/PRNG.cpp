//
// Created by ypopov on 28.05.2020.
//

#include "../Headers/PRNG.h"


uint32_t PRNG_1(uint32_t x, uint32_t y){
    uint64_t tmp = (x + y + 3) * x ;
    return (tmp >> 8) & 0xffff;
}

uint32_t PRNG_2(uint32_t x, uint32_t y){
    uint64_t tmp = ((x + y)^2 )% 1000;
    return (tmp >> 8) & 0xffff;
}
