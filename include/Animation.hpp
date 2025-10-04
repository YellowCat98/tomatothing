#pragma once

#include <Geode/Geode.hpp>

namespace tomato {
    class Animation : public cocos2d::CCSprite { // inheriting ccsprite because essentially this will just be a frame by frame animation
    private:
        std::vector<std::string> frameNames;
        float speed;
        bool init(std::vector<std::string> frameNames, float speed, std::function<void(Animation*)> onFinished);
        std::function<void(Animation*)> onFinished;
    public:
        static Animation* create(std::vector<std::string> frameNames, float speed, std::function<void(Animation*)> onFinished);
        void beginAnimation(float dt);
    };
};