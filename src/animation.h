#pragma once
#include "timer.h"
class Animation {

public:
    Timer timer;
    int frameCount;


    Animation() : timer(0), frameCount(0) {}
    Animation(int framecount, int lenght) : frameCount(frameCount), timer(lenght) {}

    float getLength() const { return timer.getLength(); }

    int currentFrame() {
        if (frameCount == 0) return 0;
        
        int frame = static_cast<int>((timer.getTime() / timer.getLength()) * frameCount);
        
        return (frame >= frameCount) ? frameCount - 1 : frame;
    }

    void step (float deltaTime) {
        timer.step(deltaTime);
    }
};
