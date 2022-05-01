#pragma once

#include <tweeny/tweeny.h>

#include "root.h"

template<typename T>
class TweenAnimation {
private:
    bool animating = false;
    bool loop = false;
    std::unique_ptr<tweeny::tween<T>> tween;
    std::function<void()> endCallback = []() {};

public:
    TweenAnimation () {};

    void onUpdate (std::function<void(T)> callback) {
        if (animating) {
            i32 ms = (i32)(Time::getDeltaTime() * 1000);
            i32 newValue = tween->step(ms);
            callback(newValue);

            if (tween->progress() >= 1) {
                if (loop) {
                    tween->seek(0);
                }
                else {
                    animating = false;
                }

                endCallback();
            }
        }
    }

public:
    inline bool isAnimating () {
        return animating;
    }

    inline void setTween (std::unique_ptr<tweeny::tween<T>>& tween) {
        // WARNING: if we copy a value type instead of a pointer, tweeny doesn't work.
        this->tween = std::move(tween);
    }

    inline void setLoop (const bool loop) {
        this->loop = loop;
    }

    inline void setEndCallback (const std::function<void()> endCallback) {
        this->endCallback = endCallback;
    }

    inline void start () {
        animating = true;
    }
};