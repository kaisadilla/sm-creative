#pragma once

#include <SFML/Graphics.hpp>

#include "root.h"
#include "SM_Time.h"
#include "assets/Assets.h"
#include "animation/AnimationState.h"
#include "animation/TweenAnimation.h"

class Particle {
protected:
    vec2 position = vec2(0, 0);
    sf::Sprite sprite;

    std::unique_ptr<SpriteAnimation> animation;
    f32 animationSpeed = 1.f;

    bool disposePending = false;

public:
    Particle() : animation() {};

    virtual void onStart();
    virtual void onUpdate();

    void destroy();

public:
    inline bool getDisposePending () {
        return disposePending;
    }

    inline void setPosition (const vec2& position) {
        this->position = position;
        sprite.setPosition(position);
    }

    inline void draw (sf::RenderWindow& window) const {
        window.draw(sprite);
    }
};