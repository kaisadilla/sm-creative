#include "game/UserInterface.h"

void UserInterface::__TEMPORARY_initialize_ui () {
    __uiFont.loadFromFile("res/bitfonts/smb3-font.json");
    __texture.loadFromFile("res/sprites/ui/ui-elements.png");

    __worldIcon.setScale(2);
    __worldIcon.setFont(__uiFont);
    __worldIcon.setPosition(18, 10);
    __worldIcon.setString("WORLD");

    __world.setScale(2);
    __world.setFont(__uiFont);
    __world.setPosition(110, 10);
    __world.setString("999");

    __livesIcon.setScale(2, 2);
    __livesIcon.setTexture(__texture);
    __livesIcon.setPosition(170, 12);
    __livesIcon.setTextureRect(sf::IntRect(0, 1, 20, 7));

    __lives.setScale(2);
    __lives.setFont(__uiFont);
    __lives.setPosition(212, 10);
    __lives.setString("99");

    __coinIcon.setScale(vec2(2, 2));
    __coinIcon.setTexture(__texture);
    __coinIcon.setPosition(624, 10);
    __coinIcon.setTextureRect(sf::IntRect(28, 0, 7, 8));

    __coins.setScale(2);
    __coins.setFont(__uiFont);
    __coins.setPosition(640, 10);
    __coins.setString("99");

    __timeIcon.setScale(vec2(2, 2));
    __timeIcon.setTexture(__texture);
    __timeIcon.setPosition(686, 12);
    __timeIcon.setTextureRect(sf::IntRect(20, 1, 8, 7));

    __time.setScale(2);
    __time.setFont(__uiFont);
    __time.setPosition(vec2(704, 10));
    __time.setString("999");

    __score.setScale(2);
    __score.setFont(__uiFont);
    __score.setPosition(vec2(624, 34));
    __score.setString("99999999");

    for (i32 i = 0; i < 3; i++) {
        __cards[i].setScale(vec2(2, 2));
        __cards[i].setTexture(__texture);
        __cards[i].setPosition(454 + (i * 50), 6);
        __cards[i].setTextureRect(sf::IntRect(0, 24, 24, 24));
    }

    for (i32 i = 0; i < 6; i++) {
        __powers[i].setScale(vec2(2, 2));
        __powers[i].setTexture(__texture);
        __powers[i].setPosition(18 + (i * 16), 34);
        __powers[i].setTextureRect(sf::IntRect(0, 8, 8, 7));
    }

    __powerOn.setScale(vec2(2, 2));
    __powerOn.setTexture(__texture);
    __powerOn.setPosition(116, 34);
    __powerOn.setTextureRect(sf::IntRect(8, 8, 15, 7));
}

void UserInterface::__TEMPORARY_draw_ui (sf::RenderWindow& window) {
    window.draw(__worldIcon);
    window.draw(__world);
    window.draw(__livesIcon);
    window.draw(__lives);
    window.draw(__coinIcon);
    window.draw(__coins);
    window.draw(__timeIcon);
    window.draw(__time);
    window.draw(__score);

    for (i32 i = 0; i < 3; i++) {
        window.draw(__cards[i]);
    }

    for (i32 i = 0; i < 6; i++) {
        window.draw(__powers[i]);
    }

    window.draw(__powerOn);
}