#pragma once

#include "root.h"
#include "ui/BitmapText.h"

class UserInterface {
private:
    BitmapFont __uiFont;
    sf::Texture __texture;

    BitmapText __worldIcon;
    sf::Sprite __livesIcon;
    sf::Sprite __coinIcon;
    sf::Sprite __timeIcon;
    sf::Sprite __cards[3];
    sf::Sprite __powers[6];
    sf::Sprite __powerOn;

    BitmapText __world;
    BitmapText __lives;
    BitmapText __coins;
    BitmapText __time;
    BitmapText __score;

public:
    void __TEMPORARY_initialize_ui();
    void __TEMPORARY_draw_ui(sf::RenderWindow& window);

public:
    inline void __TEMPORARY_update_world (const string& world) {
        __world.setString(world);
    }

    inline void __TEMPORARY_update_lives (const i32 lives) {
        __lives.setString(std::to_string(lives));
    }

    inline void __TEMPORARY_update_coins (const i32 coins) {
        __coins.setString(std::to_string(coins));
    }

    inline void __TEMPORARY_update_time (const i32 time) {
        __time.setString(std::to_string(time));
    }

    inline void __TEMPORARY_update_score (const i32 score) {
        __score.setString(std::to_string(score));
    }
};