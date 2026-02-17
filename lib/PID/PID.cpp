#include "PID.h"
#include <cmath>

PID::PID() {
    data.kp = 0.0;
    data.ki = 0.0;
    data.kd = 0.0;
    data.previous_error = 0.0;
    data.error_threshold = 0.0;
    data.integral = 0.0;
}

void PID::reset() {
    data.previous_error = 0.0;
    data.integral = 0.0;
    data.error_threshold = 0.0;
}

double PID::calculate(double setpoint, double measured_value, double dt) {
    if (dt <= 0) {
        return 0.0; // Avoid division by zero
    }

    double error = setpoint - measured_value;

    // Deadband: if error small, treat as zero
    if (std::fabs(error) <= data.error_threshold) {
        return 0.0;
    }

    data.integral += error * dt;
    double derivative = (error - data.previous_error) / dt;

    double output = data.kp * error + data.ki * data.integral + data.kd * derivative;

    data.previous_error = error;
    return output;
}