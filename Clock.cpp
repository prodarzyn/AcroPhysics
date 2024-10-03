#include "Clock.h"
#include <thread>

namespace acro {
    Clock::Clock(float targetFPS) : targetFrameTime(1.0f / targetFPS) {
        lastTime = clock::now();
    }

    Clock::time_point Clock::now() {
        return clock::now();
    }

    float Clock::getDeltaTime() {
        auto currentTime = clock::now();
        std::chrono::duration<float> deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        return deltaTime.count();
    }

    void Clock::sleepForFrame() {
        float dt = getDeltaTime();
        if (dt < targetFrameTime) {
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>((targetFrameTime - dt) * 1000)));
        }
    }
}