#include "Execute.h"

template<typename Func>
Execute::Execute(unsigned long timer, Func callback) {
    this->timer = timer;
    this->currentTime = millis();
    this->callback = callback;    
}

template<typename Func>
void Execute::atTime(unsigned long timer, Func callback) {
    if (currentTime >= timer) {
        currentTime = 0;
        if (callback) {
            callback();
        }
    }
}