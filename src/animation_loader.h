#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <map>
#include <filesystem>
#include <unordered_map>
#include <iostream>

using json = nlohmann::json;
namespace fs = std::filesystem;

struct Frame {
    int x, y, w, h;
};

enum PlayerStates { 
    SHOOTING, 
    JUMPING, 
    HURTING, 
    RUNNING, 
    STANDING, 
    COUNT };  

class AnimationLoader {
    
private:
    std::unordered_map<std::string, int> playerStringToState = {
        {"player_jumping.json", JUMPING},
        {"player_running.json", RUNNING}, 
        {"player_hurting.json", HURTING},
        {"player_standing.json",STANDING}
    };

    std::map<int, std::vector<Frame>> PlayerAnimations;
   
    void _loadCurrentAnimation(const std::string &path, std::map<int, std::vector<Frame>> &entityAnimation, int currentAnimation) {
        std::ifstream file(path);
        
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo: " << path << std::endl;
            return;
        }
        
        json data;
        file >> data;
        
        std::vector<Frame> frames;
        
        for (size_t i = 0; i < data["frames"].size(); i++) {
            Frame currentFrame;
            auto& f = data["frames"][i];
            currentFrame.x = f["frame"]["x"];
            currentFrame.y = f["frame"]["y"];
            currentFrame.w = f["frame"]["w"];
            currentFrame.h = f["frame"]["h"];
            
            frames.push_back(currentFrame);
        }
    
        entityAnimation[currentAnimation] = frames;
    }
    void _loadDirAnimations(const std::string &dirName, const std::unordered_map<std::string, int> &stringToState, std::map<int, std::vector<Frame>> &entityAnimation) {
        
        try {
            if (fs::exists(dirName) && fs::is_directory(dirName)) {
                for (const auto& entry : fs::directory_iterator(dirName)) {
                    
                    std::string fileName = entry.path().filename().string();
                    std::string fullPath = entry.path().string();
                    
                    if (stringToState.count(fileName)) {
                        int current_animation = stringToState.at(fileName);
                        _loadCurrentAnimation(fullPath, entityAnimation, current_animation);
                    }
                }
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error de filesystem: " << e.what() << std::endl;
        }
    }

public:
    std::map<int, std::vector<Frame>> getPlayerAnimations() {
        _loadDirAnimations("data/playerAnimations", playerStringToState, PlayerAnimations);
        return PlayerAnimations;
    }
};
