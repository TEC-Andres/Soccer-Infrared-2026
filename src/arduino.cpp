#include <Arduino.h>
#include <ArduinoSTL.h>
#include <vector>
#include <Wire.h>
#include "constants.h"
#include "motors.h"
#include "BNO.h"
#include "Execute.h"

Motors motors;
Bno bno;
Execute execute;

unsigned long previousTime = 0;
unsigned long currentTime = 0;

void setup() {
    Serial.begin(115200);
    // motors.begin();
    bno.begin();
    delay(2000);
    Serial.println("Setup complete");
}

void loop() {
    double yaw = bno.GetBNOData();
    Serial.print("Yaw: ");
    Serial.println(yaw);
    int base_speed = 65;
    motors.move(0, base_speed);
    execute.atTime(2000, Serial.print("test"));
    motors.move(90, base_speed);
    motors.move(180, base_speed);
    motors.move(270, base_speed);
    motors.stop();
}