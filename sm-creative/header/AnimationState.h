#pragma once

#include "root.h"
#include "Animation.h"

class AnimationState {
private:
    ui32 state = 0;
    std::vector<Animation> animations;

public:
    AnimationState(std::vector<Animation> animations);

    inline const ui32 getState () const {
        return state;
    }

    inline const Animation& getCurrentAnimation () const {
        return animations[state];
    }

    inline void setState (const ui32& state) {
        if (state != this->state) {
            this->state = state;
            animations[state].reset();
        }
    }

    inline void onUpdate(const f32 deltaTime, const f32 speed) {
        animations[state].onUpdate(deltaTime, speed);
    }
};