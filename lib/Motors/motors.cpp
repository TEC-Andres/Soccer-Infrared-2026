
#include "motors.h"

Motors::Motors() {
    left.id = 1;
    left.pwmPin = Constants::Motor::Left::pwm;
    left.in1Pin = Constants::Motor::Left::in1;
    left.in2Pin = Constants::Motor::Left::in2;

    center.id = 2;
    center.pwmPin = Constants::Motor::Center::pwm;
    center.in1Pin = Constants::Motor::Center::in1;
    center.in2Pin = Constants::Motor::Center::in2;

    right.id = 3;
    right.pwmPin = Constants::Motor::Right::pwm;
    right.in1Pin = Constants::Motor::Right::in1;
    right.in2Pin = Constants::Motor::Right::in2;
}

void Motors::begin() {
    left.begin();
    center.begin();
    right.begin();
}

void Motors::stop() {
    left.stop();
    center.stop();
    right.stop();
}

void Motors::move(float angleDegrees, float speedPercent, float rotationalSpeed) {
    float upper_left_speed = cos((angleDegrees - 150) * PI / 180.0f) * speedPercent + rotationalSpeed;
    float lower_center_speed = cos((angleDegrees - 270) * PI / 180.0f) * speedPercent + rotationalSpeed;
    float upper_right_speed = cos((angleDegrees - 30) * PI / 180.0f) * speedPercent + rotationalSpeed;

    left.setSpeed(upper_left_speed);
    center.setSpeed(lower_center_speed);
    right.setSpeed(upper_right_speed);
}

void Motors::Motor::begin() {
    pinMode(pwmPin, OUTPUT);
    pinMode(in1Pin, OUTPUT);
    pinMode(in2Pin, OUTPUT);
    stop();
}

void Motors::Motor::setSpeed(float speed) {
    speed = constrain(speed, -255.0f, 255.0f);

    if (speed < 0) {
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, HIGH);
    } else {
        digitalWrite(in1Pin, HIGH);
        digitalWrite(in2Pin, LOW);
    }

    int pwm = floor(abs(speed));
    if (id == 2) pwm -= 15; // ****Calibration for motor 2
    
    pwm = constrain(pwm, 0, 255);

    // Serial.print("Motor ");
    // Serial.print(id);
    // Serial.print(" Speed: ");
    // Serial.println(pwm);
    analogWrite(pwmPin, pwm);
}

void Motors::Motor::stop() {
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, HIGH);
    setSpeed(0);
}