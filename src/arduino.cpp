#include <Arduino.h>
#include <ArduinoSTL.h>
#include <vector>
#include "BNO.h"
#include "constants.h"
#include "robot.h"
#include "PID.h"

struct PIDParameters {
    double kp;
    double ki;
    double kd;
    double max_output;
    double min_output;
    double error_threshold;
    double target;
    double current_value;
    
    PIDParameters(double kp, double ki, double kd, double max_out, double min_out, double error_thresh)
        : kp(kp), ki(ki), kd(kd), max_output(max_out), min_output(min_out), error_threshold(error_thresh), target(0), current_value(0) {}
};

Robot robot;    
Bno bno;

#define KP 0.0
#define KI 0
#define KD 0
#define ERROR_THRESHOLD 5

void setup() {
    Serial.begin(9600);
    robot.begin();
    bno.begin();
    Serial.println("Setup complete");
    delay(2000);
}

void loop() {
    double yaw = bno.GetBNOData();
    double targetYaw = 0.0;
    PIDParameters pidParams(KP, KI, KD, Constants::Motor::maxPWM, 0, ERROR_THRESHOLD);

    pidParams.target = targetYaw;
    pidParams.current_value = yaw;
    double pidOutput = PID::calculate(pidParams);
    Serial.print(pidOutput);
    robot.move(0, 0.0, pidOutput);
}