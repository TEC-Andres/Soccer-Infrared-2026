#ifndef PHOTO_H
#define PHOTO_H

#include <Arduino.h>
#include "constants.h"
#include "Multiplexer.h"

enum class Side {
    Left,
    Right,
    Front
};

struct PhotoData {
    bool is_on_line;
    int correction_degree;
};

class Photo {
private:
    Multiplexer left_mux_;
    Multiplexer right_mux_;
    Multiplexer front_mux_;

    uint16_t photo_left_[Constants::kPhotoLeftElements];
    uint16_t photo_right_[Constants::kPhotoRightElements];
    uint16_t photo_front_[Constants::kPhotoFrontElements];

    static const int kMovingAverageSize = 10;
    uint16_t left_values_[kMovingAverageSize] = {0};
    uint16_t right_values_[kMovingAverageSize] = {0};
    uint16_t front_values_[kMovingAverageSize] = {0};
    
    int left_index_ = 0;
    int right_index_ = 0;
    int front_index_ = 0;

    uint16_t CalculateMovingAverage(uint16_t* array, int& index, uint16_t new_value);

public:
    
    Photo(uint8_t sig_left, uint8_t s0_l, uint8_t s1_l, uint8_t s2_l,
          uint8_t sig_right, uint8_t s0_r, uint8_t s1_r, uint8_t s2_r,
          uint8_t sig_front, uint8_t s0_f, uint8_t s1_f, uint8_t s2_f);
          
    uint16_t GetRawReading(Side side, uint8_t channel);          

    void Initialize();
    void ReadAllSensors(Side side); 
    PhotoData CheckPhotosOnField(Side side);
};

#endif // PHOTO_H