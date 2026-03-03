#include "photo.h"

Photo::Photo(uint8_t sig_left, uint8_t s0_l, uint8_t s1_l, uint8_t s2_l,
             uint8_t sig_right, uint8_t s0_r, uint8_t s1_r, uint8_t s2_r,
             uint8_t sig_front, uint8_t s0_f, uint8_t s1_f, uint8_t s2_f)
    : left_mux_(sig_left, s0_l, s1_l, s2_l),
      right_mux_(sig_right, s0_r, s1_r, s2_r),
      front_mux_(sig_front, s0_f, s1_f, s2_f) {}

void Photo::Initialize() {
    left_mux_.InitializeMultiplexer();
    right_mux_.InitializeMultiplexer();
    front_mux_.InitializeMultiplexer();
}

void Photo::ReadAllSensors(Side side) {
    switch (side) {
        case Side::Left:
            for (int i = 0; i < Constants::kPhotoLeftElements; i++) {
                photo_left_[i] = left_mux_.readChannel(i);
            }
            break;
            
        case Side::Right:
            for (int i = 0; i < Constants::kPhotoRightElements; i++) {
                photo_right_[i] = right_mux_.readChannel(i);
            }
            break;
            
        case Side::Front:
            for (int i = 0; i < Constants::kPhotoFrontElements; i++) {
                photo_front_[i] = front_mux_.readChannel(i);
            }
            break;
    }
}

uint16_t Photo::CalculateMovingAverage(uint16_t* array, int& index, uint16_t new_value) {
    array[index] = new_value;
    index = (index + 1) % kMovingAverageSize;
    
    uint32_t sum = 0;
    for (int i = 0; i < kMovingAverageSize; i++) {
        sum += array[i];
    }
    return sum / kMovingAverageSize;
}

PhotoData Photo::CheckPhotosOnField(Side side) {
    PhotoData data = {false, 0};
    
    ReadAllSensors(side);

    int32_t weighted_sum = 0;
    int32_t total_sensor_value = 0;
    
    // Negative means rotate left, positive means rotate right
    const int weights[8] = {-40, -30, -20, -10, 10, 20, 30, 40};
    
    // Pointers and thresholds to handle sides dynamically
    uint16_t* current_array;
    int threshold;
    int elements;

    switch (side) {
        case Side::Left:
            current_array = photo_left_;
            threshold = Constants::kPhotoTresholdLeft;
            elements = Constants::kPhotoLeftElements;
            break;
        case Side::Right:
            current_array = photo_right_;
            threshold = Constants::kPhotoTresholdRight;
            elements = Constants::kPhotoRightElements;
            break;
        case Side::Front:
            current_array = photo_front_;
            threshold = Constants::kPhotoTresholdFront;
            elements = Constants::kPhotoFrontElements;
            break;
    }

    for (int i = 0; i < elements; i++) {
        // If ANY sensor is above the threshold, we are on the line
        if (current_array[i] > threshold) {
            data.is_on_line = true;
            
            // Only use the sensors actually seeing the line for the math
            int active_value = current_array[i] - threshold; 
            
            weighted_sum += (active_value * weights[i]);
            total_sensor_value += active_value;
        }
    }

    if (data.is_on_line && total_sensor_value > 0) {
        // This calculates the "Center of Mass" of the line.
        data.correction_degree = weighted_sum / total_sensor_value; 
    } else {
        data.correction_degree = 0; // No line, no correction needed
    }

    return data;
}

uint16_t Photo::GetRawReading(Side side, uint8_t channel) {
    switch (side) {
        case Side::Left:  return photo_left_[channel];
        case Side::Right: return photo_right_[channel];
        case Side::Front: return photo_front_[channel];
        default: return 0;
    }
}