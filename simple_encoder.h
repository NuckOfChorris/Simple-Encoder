#ifndef SIMPLE_ENCODER_H
#define SIMPLE_ENCODER_H

/**
 * simple_encoder.h
 * 
 * J Webb
 * May 2022
 * 
 * Desc
 * 
 **/

#include <stdint.h>

class Encoder {
    public:
        Encoder(uint8_t A_pin, uint8_t B_pin);
        Encoder(uint8_t A_pin, uint8_t B_pin, uint8_t SW_pin);

    private:
        uint8_t hasSwitch = 0;
        uint8_t A_pin;
        uint8_t B_pin;
        uint8_t SW_pin;
        volatile uint16_t A;
        volatile uint16_t B;
        volatile uint8_t SW;
};

#endif