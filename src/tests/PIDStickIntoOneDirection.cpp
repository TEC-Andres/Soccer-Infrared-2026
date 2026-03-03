#include <Arduino.h>
#include "BNO.h"
#include "constants.h"
#include "robot.h"
#include "PID.h"

Robot robot;
Bno bno;

#define KP 80/Constants::Motor::maxPWM
#define KI 0/Constants::Motor::maxPWM
#define KD 0/Constants::Motor::maxPWM

#define ERROR_THRESHOLD 100

// // Persistent PID parameters so I/D terms accumulate across loop() calls
// PIDParameters pidParams(KP, KI, KD,
//                         Constants::Motor::maxPWM,
//                         0,
//                         ERROR_THRESHOLD);

// 0.9375/kMaxPWM, 0.01/kMaxPWM, 0.01/kMaxPWM
PID pid(KP, KI, KD, ERROR_THRESHOLD);

void setup() {
    Serial.begin(9600);
    robot.begin();
    bno.begin();
    delay(2000);
}

void loop() {
    double yaw = bno.GetBNOData();
    Serial.print("Yaw: ");
    Serial.print(yaw);
    Serial.print(" | Target Yaw: ");
    double targetYaw = 0.0;
    double pidOutput = pid.Calculate(targetYaw, yaw);
    Serial.print(" Target Yaw:");
    Serial.print(targetYaw);
    Serial.print(" Yaw: ");
    Serial.println(yaw);

    // Motor::setSpeed floors to an integer PWM value.
    // Passing 0.35f directly becomes 0 PWM, so scale to PWM units.
    const float drivePwm = 0.25f * Constants::Motor::maxPWM;
    robot.move(0, drivePwm, pidOutput);


}