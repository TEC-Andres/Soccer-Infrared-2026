#pragma once
#include <stdint.h>


namespace Constants {

    //--------------------Pines for arduino mega--------------------

    namespace Motor {
        namespace Left {
            const uint8_t in1 = 26;
            const uint8_t in2 = 27;
            const uint8_t pwm = 4;
        }

        namespace Center {
            const uint8_t in1 = 25;
            const uint8_t in2 = 24; 
            const uint8_t pwm = 5;
        }

        namespace Right {
            const uint8_t in1 = 23;
            const uint8_t in2 = 22;
            const uint8_t pwm = 6;
        }

        const double minPWM = 40.0; // We set the minimum PWM that the robot needs to move
        const double maxPWM = 255.0; // We set a max PWM to limit the motors movement for better performance and control
    }

    //--------------------Pins for multiplexer and phototransistors--------------------

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

    // Phototransistors
    const uint8_t kPhotoLeftElements = 8;
    const uint8_t kPhotoRightElements = 8;
    const uint8_t kPhotoFrontElements = 8;

    // Photo Treshold (lack of calibration, these values are just a reference and should be calibrated for better performance)
    const int kPhotoTresholdLeft = 300;
    const int kPhotoTresholdRight = 290;
    const int kPhotoTresholdFront = 315; 

    // Ultrasonic sensor
    const uint8_t kTrigPin = 33;
    const uint8_t kEchoPin = 32;

    const uint8_t kMinGoalKeeperTresholdY = 35; // Minimum distance to the goal in cm
    const uint8_t kMaxGoalKeeperTresholdY = 65; // Maximum distance to the goal in cm
    const int kLeftGoalKeeperTresholdX = 116; // Minimum distance to the goal in cm
    const int kRightGoalKeeperTresholdX = 275; // Maximum distance to the goal in cm
    const uint8_t kGoalKeeperTresholdX = 15;
}