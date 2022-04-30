#pragma once

#include "root.h"
#include "animation/SpriteAnimation.h"
#include "animation/StaticAnimation.h"
#include "animation/DynamicAnimation.h"

//template<typename T>
//using uptrv = std::vector<std::unique_ptr<T*>>;

class AnimationState {
private:
    ui32 state = 0;
    //std::vector<SpriteAnimation*> animations;
    std::vector<std::unique_ptr<SpriteAnimation>> animations;

public:
    AnimationState() {};
    AnimationState(std::vector<std::unique_ptr<SpriteAnimation>>& animations);
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

    inline void setAnimations (std::vector<std::unique_ptr<SpriteAnimation>>& animations) {
        //this->animations = std::vector<std::unique_ptr<SpriteAnimation>>(animations.size());
        //this->animations = std::vector<std::unique_ptr<SpriteAnimation>>(animations);
        this->animations = std::move(animations);
    }

    inline void clearAnimations () {
        animations.clear();
    }

    inline void addAnimation (std::unique_ptr<SpriteAnimation>& animation) {
        animations.push_back(std::move(animation));
    }

    inline void onUpdate (const f32 deltaTime, const f32 speed) {
        animations[state]->onUpdate(deltaTime, speed);
    }
};