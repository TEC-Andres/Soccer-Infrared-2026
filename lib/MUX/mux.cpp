#include "Multiplexer.h"

Multiplexer::Multiplexer(uint8_t signalPin, uint8_t s0, uint8_t s1, uint8_t s2)
    : signal_pin_(signalPin), s0_(s0), s1_(s1), s2_(s2)  {}

void Multiplexer::InitializeMultiplexer() {
    pinMode(s0_, OUTPUT);
    pinMode(s1_, OUTPUT);
    pinMode(s2_, OUTPUT);
    //pinMode(signal_pin_, INPUT);
} 

float Multiplexer::readChannel(uint8_t channel) {
    // configurate the multiplexer to select the channel
    digitalWrite(s0_, channel & 0x01);
    digitalWrite(s1_, (channel >> 1) & 0x01);
    digitalWrite(s2_, (channel >> 2) & 0x01);
    
    delayMicroseconds(100); // Allow signals to settle
    analogRead(signal_pin_);
    delayMicroseconds(50);

    return analogRead(signal_pin_);
} 

