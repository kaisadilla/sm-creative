#pragma once

#include "entities/Goomba.h"
#include "entities/Koopa.h"
#include "entities/SuperMushroom.h"
#include "assets/data/WorldMob.h"

class SceneLevel;

Mob* createEnemyForLevel(data::WorldMob mobData, SceneLevel* level);