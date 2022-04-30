#include "animation/AnimationState.h"

AnimationState::AnimationState(std::vector<std::unique_ptr<SpriteAnimation>>& animations) :
    animations(std::move(animations))
{}

void AnimationState::free () {
    //for (const auto& animation : animations) {
    //    delete animation;
    //}
}