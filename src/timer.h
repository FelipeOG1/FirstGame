#pragma once

class Timer {

    float length = 0.f;
    float time = 0.f;
    bool timeout = false;

public:

    Timer() = default;

    Timer(float len)
        : length(len), time(0.f), timeout(false)
    {}

    void step(float deltaTime) {
        timeout = false;

        time += deltaTime;

        if (time >= length && length > 0.f) {
            time -= length;     
            timeout = true;
        }
    }

    void reset() {
        time = 0.f;
        timeout = false;
    }

    float getTime() const { return time; }
    float getLength() const { return length; }
    bool isTimeout() const { return timeout; }

    void setLength(float len) {
        length = len;
        reset();
    }
};
