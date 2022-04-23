#include "entities/EntityReader.h"
#include "entities/entities.h"

Entity* EntityReader::getNextEntity (Buffer& reader) {
    Entity* entity = nullptr;

    const ui32 entityType = reader.readUInt32_LE();

    // position
    const ui16 posX = reader.readUInt16_LE();
    const ui16 posY = reader.readUInt16_LE();

    // sprite
    const ui32 spriteIndex = reader.readUInt32_LE();
    const byte entitySizeX = reader.readUInt8();
    const byte entitySizeY = reader.readUInt8();
    const byte spriteSizeX = reader.readUInt8();
    const byte spriteSizeY = reader.readUInt8();
    const byte colliderTop = reader.readUInt8();
    const byte colliderLeft = reader.readUInt8();
    const byte colliderWidth = reader.readUInt8();
    const byte colliderHeight = reader.readUInt8();
    
    if (entityType == ID_SUPER_MUSHROOM) {
        const bool startingDirectionRight = reader.readUInt8();
        const byte effectOnPlayer = reader.readUInt8(); // discarded for now

        entity = new SuperMushroom(startingDirectionRight);

    }
    else if (entityType == ID_GOOMBA) {
        const bool avoidsCliffs = reader.readUInt8();
        const bool startingDirectionRight = reader.readUInt8();

        entity = new Goomba(avoidsCliffs, startingDirectionRight);
    }
    else if (entityType == ID_KOOPA) {
        const byte shellColliderTop = reader.readUInt8();
        const byte shellColliderLeft = reader.readUInt8();
        const byte shellColliderWidth = reader.readUInt8();
        const byte shellColliderHeight = reader.readUInt8();
        const bool avoidsCliffs = reader.readUInt8();
        const bool startingDirectionRight = reader.readUInt8();
        const bool canRevive = reader.readUInt8();
        const bool playerCanGrabShell = reader.readUInt8();

        entity = new Koopa(avoidsCliffs, startingDirectionRight, canRevive, playerCanGrabShell);
        ((Koopa*)entity)->initialize(sf::IntRect(shellColliderTop, shellColliderLeft, shellColliderWidth, shellColliderHeight));
    }
    else {
        std::cerr << "Invalid entity behavior ID: " << entityType << "\n";
    }
     
    const vec2 entitySize(entitySizeX, entitySizeY);
    const vec2 spriteSize(spriteSizeX, spriteSizeY);
    const sf::IntRect collider(colliderTop, colliderLeft, colliderWidth, colliderHeight);

    entity->setDefaultSizes(entitySize, spriteSize, collider);
    entity->setSprite(spriteIndex);
    entity->initializeAnimations();

    return entity;
}
