#include <tweeny/tweeny.h>

#include "root.h"

template<typename T>
class TweenAnimation {
private:
    bool isAnimating = false;
    bool loop = false;
    std::unique_ptr<tweeny::tween<T>> tween;

public:
    TweenAnimation () {};

    void onUpdate (std::function<void(T)> callback) {
        if (isAnimating) {
            i32 ms = (i32)(Time::getDeltaTime() * 1000);
            i32 newValue = tween->step(ms);
            callback(newValue);

            if (tween->progress() >= 1) {
                if (loop) {
                    tween->seek(0);
                }
                else {
                    isAnimating = false;
                }
            }
        }
    }

public:
    inline void setTween (std::unique_ptr<tweeny::tween<T>>& tween) {
        // WARNING: if we copy a value type instead of a pointer, tweeny doesn't work.
        this->tween = std::move(tween);
    }

    inline void setLoop (const bool loop) {
        this->loop = loop;
    }

    inline void start () {
        isAnimating = true;
    }
};