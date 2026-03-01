#pragma once
#include "animation.h"
#include "timer.h"
#include <stdexcept>

class AnimationInstance {

private:
    const Animation* animation = nullptr;  
    Timer timer;

public:

    AnimationInstance() = default;

    void setAnimation(const Animation* anim) {
        if (!anim)
            throw std::runtime_error("Animation nula");

        animation = anim;
        timer.setLength(anim->duration);
    }


    void step(float deltaTime) {
        if (!animation) return;
        timer.step(deltaTime);
    }

    const Frame& getCurrentFrame() const {
        if (!animation || animation->frames.empty())
            throw std::runtime_error("AnimationInstance sin animación válida");

        float ratio = timer.getTime() / animation->duration;

        size_t index = static_cast<size_t>(ratio * animation->frames.size());

        if (index >= animation->frames.size())
            index = animation->frames.size() - 1;

        return animation->frames[index];
    }

    const std::string& getSpriteSheet() const {
        if (!animation)
            throw std::runtime_error("AnimationInstance sin animación");

        return animation->spriteSheetPath;
    }

    bool isCycleFinished() const {
        return timer.isTimeout();
    }

    SDL_Texture *currentTexture() const {
        return animation->getTexture();
    }

    
};
