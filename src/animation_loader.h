#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <filesystem>
#include <nlohmann/json.hpp> 
#include "types.h"


namespace fs = std::filesystem;
using json = nlohmann::json;

class AnimationFramesLoader {
private:
    void _loadCurrentAnimation(const std::string &path, 
                               std::map<int, std::vector<Frame>> &entityAnimation, 
                               int stateKey) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Error: No se pudo abrir " << path << std::endl;
            return;
        }

        json data;
        file >> data;

        std::vector<Frame> frames;
        // Optimizamos reservando memoria de antemano
        frames.reserve(data["frames"].size());

        for (auto& f : data["frames"]) {
            Frame currentFrame;
            currentFrame.x = f["frame"]["x"];
            currentFrame.y = f["frame"]["y"];
            currentFrame.w = f["frame"]["w"];
            currentFrame.h = f["frame"]["h"];
            
            frames.push_back(currentFrame);
        }

        entityAnimation[stateKey] = std::move(frames);
    }

public:
    void loadAnimations(const std::string &dirPath, 
                        const std::unordered_map<std::string, int> &configMap, 
                        std::map<int, std::vector<Frame>> &outAnimationMap) {
        
        try {
            if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
                std::cerr << "Directorio no encontrado: " << dirPath << std::endl;
                return;
            }

            for (const auto& entry : fs::directory_iterator(dirPath)) {
                std::string fileName = entry.path().filename().string();
                
                if (configMap.count(fileName)) {
                    int state = configMap.at(fileName);
                    std::cout << "Cargando estado " << state << " desde: " << fileName << std::endl;
                    _loadCurrentAnimation(entry.path().string(), outAnimationMap, state);
                }
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error de filesystem: " << e.what() << std::endl;
        }
    }
};
