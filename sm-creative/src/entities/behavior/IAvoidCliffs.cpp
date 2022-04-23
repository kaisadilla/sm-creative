#include "entities/behavior/IAvoidCliffs.h"

IAvoidCliffs::IAvoidCliffs(const bool avoidsCliffs, const f32 mobHeight) :
    offsetDown((i32)std::ceilf(mobHeight / 16.f)),
    avoidsCliffs(avoidsCliffs)
{}

void IAvoidCliffs::onStart () {
    debug_checkedCliffTile.setFillColor(sf::Color(255, 0, 0, 128));
    debug_checkedCliffTile.setSize(vec2(16.f, 16.f));
}

void IAvoidCliffs::checkCliffs(Mob* mob, f32 speed) {
    const ivec2& gridPos = mob->getGridPosition();

    if (mob->velocity.x < 0.f) {
        checkedCliffTile = ivec2(gridPos.x, gridPos.y + offsetDown);
    }
    else if (mob->velocity.x > 0.f) {
        checkedCliffTile = ivec2(gridPos.x + 1, gridPos.y + offsetDown);
    }

    // TODO: Uncomment.

    //const WorldTile* tileAtLeft = mob->level->getTileAt(checkedCliffTile.x, checkedCliffTile.y);
    //if (tileAtLeft == nullptr || tileAtLeft->isAirTile()) {
    //    mob->velocity.x = speed;
    //}
}

void IAvoidCliffs::drawDebugInfo_cliffDetection(sf::RenderWindow& window) {
    if (avoidsCliffs) {
        debug_checkedCliffTile.setPosition(vec2(checkedCliffTile.x * 16.f, checkedCliffTile.y * 16.f));
        window.draw(debug_checkedCliffTile);
    }
}