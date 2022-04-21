#pragma once

#include <unordered_map>
#include <any>
#include <nlohmann/json.hpp>

#include "root.h"

namespace data {
    enum class Behavior {
        Goomba,
        Koopa
    };

    class WorldMob {
        typedef nlohmann::json json;

    private:
        i32 id;
        Behavior behavior;
        std::unordered_map<string, std::any> behaviorProperties;
        string sprite;
        vec2 spriteDimensions;
        std::unordered_map<string, sf::IntRect> colliders;
        vec2 position;

    public:
        static WorldMob* readFromJson(json json_mob);

    private:
        static Behavior getBehavior(string behaviorName);

    public:
        inline i32 getId () const {
            return id;
        }

        inline Behavior getBehavior () const {
            return behavior;
        }

        template<typename T>
        inline const T getBehaviorProperty (const string& key) const {
            return (T)std::any_cast<json>(behaviorProperties.at(key));
        }

        inline const string& getSprite () const {
            return sprite;
        }

        inline const vec2& getSpriteDimensions () const {
            return spriteDimensions;
        }

        inline const sf::IntRect& getCollider (const string& key) const {
            return colliders.at(key);
        }

        inline const vec2& getPosition () const {
            return position;
        }
    };

}