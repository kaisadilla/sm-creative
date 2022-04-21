#include "animation/AnimationState.h"

AnimationState::AnimationState(const std::vector<SpriteAnimation*>& animations) :
    animations(animations)
{}

void AnimationState::free () {
    //for (const auto& animation : animations) {
    //    delete animation;
    //}
}