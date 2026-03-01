#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "types.h"
#include "animation.h"

namespace fs = std::filesystem;
using json = nlohmann::json;

class AnimationLoader {
private:

    void _loadAnimationSpriteSheet(
        std::unordered_map<Action, Animation>& outAnimationMap,
        const fs::path& basePath,
        Action currentAction)
    {
        outAnimationMap[currentAction].spreedSheetPath = basePath.string();
    }

    void _loadAnimationFrames(
        std::unordered_map<Action, Animation>& outAnimationMap,
        const fs::path& basePath,
        Action currentAction)
    {
        std::ifstream file(basePath);
        if (!file.is_open()) {
            std::cerr << "Error: No se pudo abrir " << basePath << std::endl;
            return;
        }

        json data;
        file >> data;

        std::vector<Frame> frames;
        frames.reserve(data["frames"].size());

        for (auto& f : data["frames"]) {
            Frame frame;
            frame.x = f["frame"]["x"];
            frame.y = f["frame"]["y"];
            frame.w = f["frame"]["w"];
            frame.h = f["frame"]["h"];
            frames.push_back(frame);
        }

        outAnimationMap[currentAction].frames = std::move(frames);
    }

public:

    void loadAnimations(
        const std::string& dirPath,
        const std::unordered_map<std::string, Action>& configMap,
        std::unordered_map<Action, Animation>& outAnimationMap)
    {
        try {
            if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
                std::cerr << "Directorio no encontrado: " << dirPath << std::endl;
                return;
            }

            for (const auto& entry : fs::directory_iterator(dirPath)) {

                std::string stem = entry.path().stem().string();

                if (!configMap.count(stem))
                    continue;

                Action action = configMap.at(stem);
                auto ext = entry.path().extension();

                if (ext == ".png") {
                    _loadAnimationSpriteSheet(outAnimationMap, entry.path(), action);
                }
                else if (ext == ".json") {
                    _loadAnimationFrames(outAnimationMap, entry.path(), action);
                }
            }

        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error de filesystem: " << e.what() << std::endl;
        }
    }
};
