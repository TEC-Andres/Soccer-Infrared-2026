#include <Arduino.h>

    const uint8_t kPhotoLeftElements = 8;
    const uint8_t kPhotoRightElements = 8;
    const uint8_t kPhotoFrontElements = 8;

    const uint8_t kSignalPin1 = A6; 
    const uint8_t kMUXPin1_1 = 14; 
    const uint8_t kMUXPin2_1 = 15;
    const uint8_t kMUXPin3_1 = 16;

    const uint8_t kSignalPin2 = A8;
    const uint8_t kMUXPin1_2 = 17;
    const uint8_t kMUXPin2_2 = 28;
    const uint8_t kMUXPin3_2 = 29;

    const uint8_t kSignalPin3 = A7;
    const uint8_t kMUXPin1_3 = 43;
    const uint8_t kMUXPin2_3 = 44;
    const uint8_t kMUXPin3_3 = 45;

int chtm (uint8_t signalPin, uint8_t s0, uint8_t s1, uint8_t s2, uint8_t channel){
    
    digitalWrite(s0, channel & 0x01);
    digitalWrite(s1, (channel >> 1) & 0x01);
    digitalWrite(s2, (channel >> 2) & 0x01);
    
    delayMicroseconds(15); // Allow signals to settle
    analogRead(signalPin);
    delayMicroseconds(10);

    return analogRead(signalPin);
}

void setup() {
    Serial.begin(115200);
    pinMode(kMUXPin1_1, OUTPUT); pinMode(kMUXPin2_1, OUTPUT); pinMode(kMUXPin3_1, OUTPUT);
    pinMode(kMUXPin1_2, OUTPUT); pinMode(kMUXPin2_2, OUTPUT); pinMode(kMUXPin3_2, OUTPUT);
    pinMode(kMUXPin1_3, OUTPUT); pinMode(kMUXPin2_3, OUTPUT); pinMode(kMUXPin3_3, OUTPUT);
    
    delay(1000);
    Serial.println("Starting MUX test...");
    delay(1000);
}

void loop() {
    // Right
for (uint8_t i = 0; i < kPhotoLeftElements; i++) {
        int valor = chtm(kSignalPin1, kMUXPin1_1, kMUXPin2_1, kMUXPin3_1, i);
        Serial.print(">M1_C"); Serial.print(i); Serial.print(":"); Serial.println(valor);
    }
    delay(250);
for (uint8_t i = 0; i < kPhotoRightElements; i++) {
        int valor = chtm(kSignalPin2, kMUXPin1_2, kMUXPin2_2, kMUXPin3_2, i);
        Serial.print(">M2_C"); Serial.print(i); Serial.print(":"); Serial.println(valor);
    }
    delay(250);
for (uint8_t i = 0; i < kPhotoFrontElements; i++) {
        int valor = chtm(kSignalPin3, kMUXPin1_3, kMUXPin2_3, kMUXPin3_3, i);
        Serial.print(">M3_C"); Serial.print(i); Serial.print(":"); Serial.println(valor);
    }
    delay(250);
}