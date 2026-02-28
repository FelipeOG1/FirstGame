
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

enum PlayerStates { SHOOTING, JUMPING, HURTING, RUNNING, COUNT };

class AnimationLoader {
    
private:
   
    std::map<int, std::vector<Frame>> _loadAnimations(const std::string &path) {
	
        std::ifstream file (path);
        
        if (!file.is_open()) {
        
            return {};
        }

        json data;
        
        file >> data;
        
        std::vector<Frame> frames;
        
        std::map<int, std::vector<Frame>> animations;
        
        for (size_t i = 0; i < data["frames"].size(); i++) {

            Frame currentFrame;
            auto& f = data["frames"][i];
            currentFrame.x = f["frame"]["x"];
            currentFrame.y = f["frame"]["y"];
            currentFrame.w = f["frame"]["w"];
            currentFrame.h = f["frame"]["h"];
            
            frames.push_back(currentFrame);
        
        }

        
        
        return animations;


    };

    void _iterate_files(const std::string &dirName) {

        std::unordered_map<std::string, PlayerStates> stringToState = {
            {"shooting.json", SHOOTING},
            {"player_run.json", JUMPING},
            {"player_hurt.json", HURTING},
            {"running.json", RUNNING}
        };

        try {
            if (fs::exists(dirName) && fs::is_directory(dirName)) {
            
                for (const auto& entry : fs::directory_iterator(dirName)) {
                    
                    auto path_name = entry.path().filename().string();
                    
                    if (stringToState.count(path_name)) {

                        std::cout << stringToState[path_name] << std::endl;
                    }
                
                }
            }
        
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        
    };

    
    
};





