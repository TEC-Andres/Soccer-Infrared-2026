#include <Arduino.h>
#include "Multiplexer.h" 
#include "constants.h"   

Multiplexer left_mux_(Constants::kSignalPin1, Constants::kMUXPin1_1, Constants::kMUXPin2_1, Constants::kMUXPin3_1);
Multiplexer right_mux_(Constants::kSignalPin2, Constants::kMUXPin1_2, Constants::kMUXPin2_2, Constants::kMUXPin3_2);
Multiplexer front_mux_(Constants::kSignalPin3, Constants::kMUXPin1_3, Constants::kMUXPin2_3, Constants::kMUXPin3_3);

void setup() {
    Serial.begin(115200); 
    
    left_mux_.InitializeMultiplexer();
    right_mux_.InitializeMultiplexer();
    front_mux_.InitializeMultiplexer();
    
    // Wait
    delay(1000);
    Serial.println("Starting MUX test enviroment...");
}

void loop() {
    // MUX 1  
    for (uint8_t i = 0; i < 8; i++) {
        int value = left_mux_.readChannel(i);
        Serial.print("Left : C"); Serial.print(i); Serial.print(" : "); Serial.println(value);
    }
    delay(250); // delay between switching MUX as to rule out any interference between them.

    //MUX 2 
    for (uint8_t i = 0; i < 8; i++) {
        int value = right_mux_.readChannel(i);
        Serial.print("Right: C"); Serial.print(i); Serial.print(" : "); Serial.println(value);
    }
    delay(350);

    //MUX 3 
    for (uint8_t i = 0; i < 8; i++) {
        int value = front_mux_.readChannel(i);
        Serial.print("Front: C"); Serial.print(i); Serial.print(" : "); Serial.println(value);
    }
    delay(350); 
}