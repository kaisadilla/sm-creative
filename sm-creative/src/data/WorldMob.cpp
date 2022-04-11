#include "data/WorldMob.h"

namespace data {
    WorldMob* WorldMob::readFromJson (json json_mob) {
        WorldMob* mob = new WorldMob();

        mob->id = json_mob["id"];
        mob->behavior = getBehavior(json_mob["behavior"]);
        mob->sprite = json_mob["sprite"];
        mob->spriteDimensions = vec2(json_mob["dimensions"]["sprite"][0], json_mob["dimensions"]["sprite"][1]);
        mob->position = vec2(json_mob["position"][0], json_mob["position"][1]);

        for (auto& property : json_mob["behaviorProperties"].get<json::object_t>()) {
            mob->behaviorProperties[property.first] = std::any((json)property.second);
        }
        for (auto& collider : json_mob["dimensions"].get<json::object_t>()) {
            if (collider.first != "sprite") {
                auto& c = collider.second;
                mob->colliders[collider.first] = sf::IntRect(c[0], c[1], c[2], c[3]);
            }
        }

        return mob;
    }
    Behavior WorldMob::getBehavior (string behaviorName) {
        if (behaviorName == "goomba") return Behavior::Goomba;
        else if (behaviorName == "koopa")  return Behavior::Koopa;
        return Behavior::Goomba;
    }
}