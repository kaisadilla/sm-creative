#include "vfx/EarnedCoinParticle.h"
#include <tweeny/tween.h>
#include <memory>

EarnedCoinParticle::EarnedCoinParticle () {
    sprite.setTexture(Assets::particleTextures["volatile_coin"]);
    animation = std::make_unique<DynamicAnimation>(uvec2(4, 1), vec2(16, 16), 0.1f, std::vector<ui32>{0, 1, 2, 3});

    //auto& tween = tweeny::uptrFrom(0);
    auto tweeno = tweeny::from(0);
    std::unique_ptr<tweeny::tween<i32>> tween = std::make_unique<tweeny::tween<i32>>(std::move(tweeno));
    tween->to(-64).during(400).via(tweeny::easing::sinusoidalOut).to(-18).during(250).via(tweeny::easing::sinusoidalIn);
    animHeight.setTween(tween);
    animHeight.setEndCallback([this]() { destroy(); });
}

void EarnedCoinParticle::onStart () {
    Particle::onStart();
    initialPosition = position;
    animHeight.start();
}

void EarnedCoinParticle::onUpdate () {
    Particle::onUpdate();
    animHeight.onUpdate([this](i32 height) {
        setPosition(initialPosition + vec2(0, height));
    });
}