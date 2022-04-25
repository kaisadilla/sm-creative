#include "tiles/PlatformTop.h"

bool PlatformTop::hasMobCollided(const Collision& collision, const vec2& mobVelocity) const {
    return (collision.direction == Direction::DOWN && mobVelocity.y > 0.f);
}
