#pragma once

class PID {
public:
    struct PIDStruct {
        double kp;
        double ki;
        double kd;

        double previous_error = 0.0;
        double error_threshold = 0.0;
        double integral = 0.0;
    };

    // Instance holding PID parameters and state
    PIDStruct data;

    PID();
    void reset();
    double calculate(double setpoint, double measured_value, double dt);
};