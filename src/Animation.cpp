#include <Animation.hpp>

using namespace geode::prelude;

bool tomato::Animation::init(std::vector<std::string> frameNames, float speed, std::function<void(Animation*)> onFinished) {
    if (!CCSprite::init()) return false;
    this->schedule(schedule_selector(tomato::Animation::beginAnimation), 0.1f/speed);
    this->frameNames = frameNames;
    this->onFinished = onFinished;
    
    return true;
}

void tomato::Animation::beginAnimation(float dt) {
    static int frame = 1;
    const int maxFrames = this->frameNames.size();
    if (frame == maxFrames) {
        this->onFinished(this);
        frame = 1; // auto return to frame 1 so that the animation can be replayed
        return;
    }

    auto spriteName = fmt::format("{}"_spr, frameNames[frame-1]); // this is NOT lua. thou index shall start at 0.

    auto sprframe = CCSpriteFrameCache::get()->spriteFrameByName(spriteName.c_str());
    
    if (sprframe) this->setDisplayFrame(sprframe);

    ++frame;
}

tomato::Animation* tomato::Animation::create(std::vector<std::string> frameNames, float speed, std::function<void(Animation*)> onFinished) {
    auto ret = new tomato::Animation();
    if (ret && ret->init(frameNames, speed, onFinished)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}