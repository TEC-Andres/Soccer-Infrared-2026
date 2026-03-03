#include "photo.h"
#include "robot.h"
#include "PID.h"
#include "BNO.h"

#define KP (80.0f / Constants::Motor::maxPWM)
#define KI 0.0f
#define KD 0.0f
#define ERROR_THRESHOLD 100

const uint8_t kPhotoLeftElements = 8;
const uint8_t kSignalPin1 = A6; 
const uint8_t kMUXPin1_1 = 14; 
const uint8_t kMUXPin2_1 = 15;
const uint8_t kMUXPin3_1 = 16;

Robot robot;
Bno bno;
PID pid(KP, KI, KD, ERROR_THRESHOLD); 
Photo photoRight(kSignalPin1, kMUXPin1_1, kMUXPin2_1, kMUXPin3_1, 0,0,0,0, 0,0,0,0);

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    robot.begin();
    bno.begin();
    photoRight.Initialize(); 
}

void loop() {
    //pid Calculation

    double yaw = bno.GetBNOData();
    double targetYaw = 0.0;
    double pidOutput = pid.Calculate(targetYaw, yaw);

    // Line detection 
    PhotoData data = photoRight.CheckPhotosOnField(Side::Left);
    
    float speed = 0.25f * Constants::Motor::maxPWM;

Serial.print("MUX Values: ");
    for (uint8_t i = 0; i < kPhotoLeftElements; i++) {
        Serial.print(photoRight.GetRawReading(Side::Left, i));
        Serial.print(i < kPhotoLeftElements - 1 ? ", " : " ");
    }
    
    if (data.is_on_line) {
        float escapeAngle = 90.0f + data.correction_degree; 
        robot.move(escapeAngle, speed, pidOutput);

        
        Serial.print("Line detected, Correction Degree: ");
        Serial.println(data.correction_degree);
    } 
    else {
        robot.stop();
        Serial.println("No line detected, stopping motors.");
        // Normal movement until line is detected
        robot.move(0, speed, pidOutput);
    }

    delay(10); 
}
