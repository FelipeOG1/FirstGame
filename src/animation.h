#pragma once
#include "timer.h"
#include "string"
#include "map"
#include "vector"
#include "types.h"
class Animation {

public:
    Timer timer;
    int frameCount;
    std::string spreedSheetPath;
    std::vector<Frame> frames;
    
    Animation() : timer(0), frameCount(0) {}
    Animation(int count, 
              float len, 
              std::string spreedSheetPath, 
              std::map<int, std::vector<Frame>> &framesRef) 
            : frameCount(count), timer(len), spreedSheetPath(spreedSheetPath)
        {}

    
    float getLength() const { return timer.getLength(); }

    int currentFrame() {
        if (frameCount == 0) return 0;
        
        int frame = static_cast<int>((timer.getTime() / timer.getLength()) * frameCount);
        
        return (frame >= frameCount) ? frameCount - 1 : frame;
    }

    void step (float deltaTime) {
        timer.step(deltaTime);
    }

    
    Frame updateAndGetFrame(int entityState, float deltatime) {
        step(deltatime);

        if (!frames || frames->find(entityState) == frames->end()) {
            return {0, 0, 0, 0}; 
        }
        
        std::vector<Frame>& currStateFrames = frames->at(entityState);
        int index = currentFrame();
        
        return currStateFrames[index];
        
        
    }

    

};


      

