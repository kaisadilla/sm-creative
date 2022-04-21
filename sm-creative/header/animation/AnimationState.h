#pragma once

#include "root.h"
#include "animation/SpriteAnimation.h"
#include "animation/StaticAnimation.h"
#include "animation/DynamicAnimation.h"

class AnimationState {
private:
    ui32 state = 0;
    std::vector<SpriteAnimation*> animations;

public:
    AnimationState() {};
    AnimationState(const std::vector<SpriteAnimation*>& animations);
    void free();

public:
    inline const ui32 getState () const {
        return state;
    }

    inline const SpriteAnimation& getCurrentAnimation () const {
        return *(animations[state]);
    }

    inline void setState (const ui32& state) {
        if (state != this->state) {
            this->state = state;
            animations[state]->reset();
        }
    }

    inline void setAnimations (const std::vector<SpriteAnimation*>& animations) {
        this->animations = std::vector<SpriteAnimation*>(animations);
    }

    inline void onUpdate (const f32 deltaTime, const f32 speed) {
        animations[state]->onUpdate(deltaTime, speed);
    }
};