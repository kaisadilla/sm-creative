#include "Animation.h"

Animation::Animation (sf::Texture* pointer, uvec2 imageCount, f32 switchTime)
    : imageCount(imageCount), switchTime(switchTime), totalTime(0)
{
    
}

Animation::~Animation () {

}
