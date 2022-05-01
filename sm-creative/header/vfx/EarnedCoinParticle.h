#pragma once

#include "Particle.h"

class EarnedCoinParticle : public Particle {
private:
    vec2 initialPosition = vec2(0, 0);
    TweenAnimation<i32> animHeight;

public:
    EarnedCoinParticle();

    void onStart() override;
    void onUpdate() override;
};