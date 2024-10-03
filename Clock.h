#pragma once
#include <chrono>

namespace acro {
    class Clock {
    public:
        using clock = std::chrono::high_resolution_clock;
        using time_point = std::chrono::time_point<clock>;

        Clock(float targetFPS = 60.0f);

        time_point now();

        float getDeltaTime();

        void sleepForFrame();

    private:
        time_point lastTime;
        float targetFrameTime;
    };
}