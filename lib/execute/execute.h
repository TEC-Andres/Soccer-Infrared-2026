#pragma once
#include <Arduino.h>

class Execute
{
public:
    template<typename Func>
    Execute(unsigned long timer, Func callback) {
        this->timer = timer;
        this->callback = callback;
    }
    
    template<typename Func>
    void atTime(unsigned long timer, Func callback) {};
private:
    unsigned long timer;
    unsigned long currentTime;
    void(*callback)() = nullptr;
};