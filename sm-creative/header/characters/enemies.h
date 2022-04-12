#pragma once

#include "characters/Goomba.h"
#include "characters/Koopa.h"
#include "data/WorldMob.h"

class SceneLevel;

Mob* createEnemyForLevel(data::WorldMob mobData, SceneLevel* level);