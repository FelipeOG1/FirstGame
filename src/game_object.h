#pragma once
#include "animation.h"
#include <vector>
#include <unordered_map>
#include "animationInstance.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <glm/glm.hpp>


class GameObject{

protected:
    std::unordered_map<Action, Animation>& animations;
    AnimationInstance currentAnimation;
    Action currentAction = Action::IDLE;
    glm::vec2 position{ 0.0f }, aceleration { 0.0f }, velocity {0.0f}, size {0.0f};
    float direction{ 1 };
    float scale{ 1 };
    
public:
    GameObject(std::unordered_map<Action, Animation>& anims)
        : animations(anims)
    {
        if (!animations.count(Action::IDLE))
            throw std::runtime_error("Falta animación IDLE");
        
        setAction(currentAction);
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

    void setDurationAnimation(Action action, float duration) {
        try {
            Animation& animation = animations.at(action); 
            animation.setDuration(duration);
            if (currentAction == action) {
            currentAnimation.setAnimation(&animation);
            }
            
        } catch(const std::out_of_range& e) {
            std::cerr << "Llave inválida: " << e.what() << std::endl;
        } 
    
       
        
    }
   

    virtual void update(float deltaTime) {
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
        SDL_Texture* tex = currentAnimation.getTexture();
        if (!tex) return;
       

        SDL_FRect hitbox = { 
        this->position.x,          
        this->position.y,                  
        float(f.w) * this->scale, 
        float(f.h) * this->scale,
        };
       
        SDL_FRect dst = { 
        this->position.x,          
        this->position.y,                  
        float(f.w) * this->scale, 
        float(f.h) * this->scale,
        };
        
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);//GREEN
        SDL_RenderRect(renderer, &hitbox);//render heatbox


        SDL_FRect src = { (float)f.x, (float)f.y, (float)f.w, (float)f.h };


        SDL_FlipMode flip = direction == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        SDL_RenderTextureRotated(renderer, tex, &src, &dst, 0.0, nullptr, flip);
    };



    virtual ~GameObject() = default;
 
};   
