#pragma once
#include "animation.h"
#include <vector>
#include <unordered_map>
#include "animationInstance.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Player {

private:
    const std::unordered_map<Action, Animation>& animations;
    AnimationInstance currentAnimation;
    Action currentAction = Action::IDLE;
public:

    float x, y;

    Player(const std::unordered_map<Action, Animation>& anims)
        : animations(anims) , x(0.0f), y(0.0f)
    {
        if (!animations.count(Action::IDLE))
            throw std::runtime_error("Falta animación IDLE");
        
        setAction(Action::IDLE);
        currentAnimation.setAnimation(&animations.at(currentAction));
    }

    void setAction(Action newAction) {
        if (currentAction != newAction) {

            if (!animations.count(newAction))
                throw std::runtime_error("Animación no encontrada");

            currentAction = newAction;
            currentAnimation.setAnimation(&animations.at(currentAction));
        }
    }

    void update(float deltaTime) {
        currentAnimation.step(deltaTime);
    }

    const Frame& getCurrentFrame() const {
        return currentAnimation.getCurrentFrame();
    }

    const std::string& getCurrentSpriteSheet() const {
        return currentAnimation.getSpriteSheet();
    }

    Action getCurrentAction() const {
        return currentAction;
    }

    void draw(SDL_Renderer *renderer) {
        const Frame& f = getCurrentFrame();
        SDL_Texture* tex = currentAnimation.currentTexture();
        if (!tex) return;

        SDL_FRect src = { (float)f.x, (float)f.y, (float)f.w, (float)f.h };
        
        SDL_FRect dst = { 
        this->x,          
        this->y,                  
        f.w * 2.0f, 
        f.h * 2.0f 
        };
        SDL_RenderTexture(renderer, tex, &src, &dst);
    };
         
    };

        
    
