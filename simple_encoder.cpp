
/**
 * simple_encoder.cpp
 * 
 * J Webb
 * May 2022
 * 
 * Desc
 * 
 **/

#include "simple_encoder.h"
#include "PinChangeInterrupt.h"     // nicohood/PinChangeInterrupt@^1.2.9
#include <Arduino.h>

Encoder::Encoder(uint8_t A_PIN, uint8_t B_PIN) {
    attachPCINT(digitalPinToPCINT(A_PIN), encoder_int_handler_A, CHANGE);
    attachPCINT(digitalPinToPCINT(B_PIN), encoder_int_handler_B, CHANGE);
    A_pin = A_PIN;
    B_pin = B_PIN;
}

Encoder::Encoder(uint8_t A_PIN, uint8_t B_PIN, uint8_t SW_PIN) {
    attachPCINT(digitalPinToPCINT(A_PIN), encoder_int_handler_A, CHANGE);
    attachPCINT(digitalPinToPCINT(B_PIN), encoder_int_handler_B, CHANGE);
    A_pin = A_PIN;
    B_pin = B_PIN;
    SW_pin = SW_PIN;
    pinMode(SW_PIN, INPUT);
    hasSwitch = 1;
}

void Encoder::encoder_int_handler_A(void) {
    // Read the pin states
    A = digitalRead(A_pin);
    B = digitalRead(B_pin);

    if (ISR_cooldown_ready()) {
        // Phase A
        if (A) {
            if (B) {
                enc_pos--;            // CCW
            } else {
                enc_pos++;            // CW
            }
        } else {
            if (B) {
                enc_pos++;            // CW
            } else {
                enc_pos--;            // CCW
            }
        }
    }
}

void Encoder::encoder_int_handler_B(void) {
    // Read the pin states
    A = digitalRead(A_pin);
    B = digitalRead(B_pin);

    if (ISR_cooldown_ready()) {
        // Phase B
        if (B) {
            if (A) {
                enc_pos++;            // CW
            } else {
                enc_pos--;            // CCW
            }
        } else {
            if (A) {
                enc_pos--;            // CCW
            } else {
                enc_pos++;            // CW
            }
        }
    }
}

uint8_t Encoder::read_switch(void) {
    SW = digitalRead(SW_pin);
    return SW;
}

uint8_t Encoder::ISR_cooldown_ready(void) {
    uint8_t ret = 0;
    uint32_t t = millis();
    if ((t - ISR_timestamp) > ISR_period) {
        ret = 1;
    }
    ISR_timestamp = t;
    return ret;
}