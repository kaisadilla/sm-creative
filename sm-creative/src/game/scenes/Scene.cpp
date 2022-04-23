#include "game/scenes/Scene.h"

void Scene::setWindowSize (const uvec2& size, const vec2& zoom) {
    windowSize = size;
    windowZoom = zoom;
}
