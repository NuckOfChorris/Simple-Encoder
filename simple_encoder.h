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
        Encoder(uint8_t A_PIN, uint8_t B_PIN);
        Encoder(uint8_t A_PIN, uint8_t B_PIN, uint8_t SW_PIN);
        uint8_t read_switch(void);

    private:
        uint8_t hasSwitch = 0;
        uint8_t A_pin;
        uint8_t B_pin;
        uint8_t SW_pin;
        uint8_t SW;
        volatile uint8_t A;
        volatile uint8_t B;
        volatile int32_t enc_pos = 0;
        volatile uint32_t ISR_timestamp = 0;
        const uint16_t ISR_period = 100;        // ms

        void encoder_int_handler_A(void);
        void encoder_int_handler_B(void);
        uint8_t ISR_cooldown_ready(void);
};

#endif