#include "entities/Player.h"
#include "entities/Item.h"
#include "entities/Enemy.h"
#include "game/scenes/LevelScene.h"

Player::Player () {
    destroyWhenOutOfBounds = false;
    sound_jump.setBuffer(Assets::sound_jump);
    sound_death.setBuffer(Assets::sound_playerDeath);
}

GameObjectType Player::getType () {
    return GameObjectType::Player;
}

void Player::__TEMPORARY_initialize_animations () {
    std::unique_ptr<SpriteAnimation> aSmallStill    = std::make_unique<StaticAnimation >(uvec2(16, 8), textureSize, 0);
    std::unique_ptr<SpriteAnimation> aSmallWalking  = std::make_unique<DynamicAnimation>(uvec2(16, 8), textureSize, 0.1f, std::vector<ui32>{ 0, 1 });
    std::unique_ptr<SpriteAnimation> aSmallSkidding = std::make_unique<StaticAnimation >(uvec2(16, 8), textureSize, 3);
    std::unique_ptr<SpriteAnimation> aSmallJumping  = std::make_unique<StaticAnimation >(uvec2(16, 8), textureSize, 2);
    std::unique_ptr<SpriteAnimation> aDead          = std::make_unique<StaticAnimation >(uvec2(16, 8), textureSize, 4);
    std::unique_ptr<SpriteAnimation> aBigStill      = std::make_unique<StaticAnimation >(uvec2(16, 8), textureSize, 16);
    std::unique_ptr<SpriteAnimation> aBigWalking    = std::make_unique<DynamicAnimation>(uvec2(16, 8), textureSize, 0.075f, std::vector<ui32>{ 16, 17, 18, 17 });
    std::unique_ptr<SpriteAnimation> aBigSkidding   = std::make_unique<StaticAnimation >(uvec2(16, 8), textureSize, 20);
    std::unique_ptr<SpriteAnimation> aBigJumping    = std::make_unique<StaticAnimation >(uvec2(16, 8), textureSize, 19);
    std::unique_ptr<SpriteAnimation> aBigCrouching  = std::make_unique<StaticAnimation >(uvec2(16, 8), textureSize, 21);

    // TODO: idk what I will do with this.
    DynamicAnimation* aTransformSmallToBig = new DynamicAnimation({ 16, 8 }, textureSize, 0.0666f, { 22, 0, 22, 0, 22, 0, 22, 16, 22, 16, 22, 16 }, [this]() {
        std::cout << "Nothing happens here yet";
    });

    animations.addAnimation(aSmallStill);
    animations.addAnimation(aSmallWalking);
    animations.addAnimation(aSmallSkidding);
    animations.addAnimation(aSmallJumping);
    animations.addAnimation(aDead);
    animations.addAnimation(aBigStill);
    animations.addAnimation(aBigWalking);
    animations.addAnimation(aBigSkidding);
    animations.addAnimation(aBigJumping);
    animations.addAnimation(aBigCrouching);
}

void Player::onStart () {
    Entity::onStart();
}

void Player::onUpdate () {
    Entity::onUpdate();
    input();
    setAnimationState();
}

void Player::onFixedUpdate () {
    Entity::onFixedUpdate();
    checkLevelBoundaries();
}

void Player::onCollisionWithTile (Collision& collision, Tile& tile) {
    if (collision.direction == Direction::UP) {
        playerJumpEnd(true);
    }

    tile.onCollisionWithPlayer(collision, this);
}

void Player::input () {
    if (jumpBufferTime > 0.f) {
        jumpBufferTime -= Time::getDeltaTime();
    }

    f32 acc = ACCELERATION_X * Time::getDeltaTime();
    f32 maxSpeed = MAX_SPEED_X;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
        maxSpeed *= 1.555f; // Original goes to 18 to 28, which is ~1.5555555555-.
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
        maxSpeed = 2.f;
    }
    if (!isGrounded) {
        acc *= 0.75f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        if (velocity.x > 0.f) {
            acc *= 2.f;
        }
        velocity.x = std::fmaxf(-maxSpeed, velocity.x - acc);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        if (velocity.x < 0.f) {
            acc *= 2.f;
        }
        velocity.x = std::fminf(maxSpeed, velocity.x + acc);
    }
    else {
        if (isGrounded) {
            // Start losing speed if the player is moving, or stop completely when below 0.1 abs horizontal speed.
            if (velocity.x < 0.1f) {
                velocity.x = std::fminf(0.f, velocity.x + (ACCELERATION_X * Time::getDeltaTime()));
            }
            else if (velocity.x > 0.1f) {
                velocity.x = std::fmaxf(0.f, velocity.x - (ACCELERATION_X * Time::getDeltaTime()));
            }
            else {
                velocity.x = 0.f;
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
        if (isJumping) {
            playerJump();
        }
        // queue up a jump command, whether or not the player can jump now.
        else if (!isJumping && jumpReleased) {
            jumpBufferTime = JUMP_BUFFER;
        }

        // if there's a jump command queued up and the player can jump, do so.
        if (jumpBufferTime > 0.f && isGrounded) {
            playerJumpStart();
        }

        jumpReleased = false;
    }
    else if (isJumping) {
        playerJumpEnd(false);
    }
    else {
        jumpReleased = true;
    }
}

void Player::playerJumpStart () {
    jumpStart = Time::getTime();
    jumpTime = 0.f;
    jumpMinTime = 0.08f;
    jumpMaxTime = 0.4f;
    isJumping = true;

    sound_jump.play();

    gravityScale = 0.f;
    playerJump();
}

void Player::playerJump () {
    if (isJumping) {
        jumpTime += Time::getDeltaTime();
        if (jumpTime > jumpMaxTime) {
            playerJumpEnd(false);
        }
        else {
            velocity.y = (-16.f * 4.f) / 0.4f;
        }
    }
}

void Player::playerJumpEnd (bool forced) {
    if (isJumping) {
        if (!forced && jumpTime < jumpMinTime) {
            playerJump();
        }
        else {
            gravityScale = 1.f;
            isJumping = false;
            jumpTime = 0.f;
        }
    }
}

void Player::setMode (MarioMode mode) {
    if (mode == MarioMode::BIG) {
        currentMode = mode;
    }
    updateColliderDimensions();
}

void Player::takeDamage(bool forceDeath, Direction direction) {
    die();
}

void Player::die () {
    Entity::die();
    sound_death.play();
}

void Player::earnCoin () {
    level->addCoins(1);
    level->addScore(100);
}
 
void Player::setAnimationState () {
    animationSpeed = 1.f;
    if (isDead) {
        animations.setState(AnimState::ANIM_DEAD);
    }
    else {
        if (isGrounded) {
            if (velocity.x == 0) {
                animations.setState(getCurrentAnimState_still());
            }
            else if (velocity.x < 0.f) {
                // if the player is moving left but pressing right, they are skidding.
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                    animations.setState(getCurrentAnimState_skid());
                }
                else {
                    animationSpeed = std::abs(velocity.x / 64.f);
                    animations.setState(getCurrentAnimState_walking());
                }
            }
            else if (velocity.x > 0.f) {
                // if the player is moving right but pressing left, they are skidding.
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                    animations.setState(getCurrentAnimState_skid());
                }
                else {
                    animationSpeed = std::abs(velocity.x / 64.f);
                    animations.setState(getCurrentAnimState_walking());
                }
            }
        }
        else {
            animations.setState(getCurrentAnimState_jumping());
        }
    }
}

void Player::checkLevelBoundaries () {
    if (position.x < 0) {
        position.x = 0;
    }
    else if (position.x > level->getPixelWidth() - size.y) {
        position.x = level->getPixelWidth() - size.y;
    }
}

void Player::checkLookingLeft () {
    Entity::checkLookingLeft();

    // TODO: This could probably be simplified as "the player is always looking in the direction he's pressing".
    // when skidding, the player is looking at the direction he's trying to move in.
    if (velocity.x < 0.f && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        isLookingLeft = false;
    }
    else if (velocity.x > 0.f && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        isLookingLeft = true;
    }

    // when airborne, the player is looking at the direction he's trying to look in.
    if (!isGrounded) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            isLookingLeft = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            isLookingLeft = false;
        }
    }
}

void Player::updateColliderDimensions () {
    if (currentMode == MarioMode::SMALL) {
        setColliderSize(sf::IntRect(11, 18, 10, 14));
    }
    else if (currentMode == MarioMode::BIG) {
        setColliderSize(sf::IntRect(10, 7, 12, 25));
    }
}