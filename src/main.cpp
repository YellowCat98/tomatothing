#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Animation.hpp>

using namespace geode::prelude;

#define CREATE_TOMATO_ANIM(var, speed, onFinished) \
std::vector<std::string> ___frames; \
for (int i = 0; i <= 118; ++i) { \
	___frames.push_back(fmt::format("frame_{:04}.png", i)); \
} \
var = tomato::Animation::create(___frames, speed, onFinished) \

class $modify(CoolerPlayLayer, PlayLayer) {
	void coolerPauseGame(bool p0) {
		
		PlayLayer::pauseGame(p0);
		auto pauselayer = static_cast<PauseLayer*>(CCScene::get()->getChildByID("PauseLayer"));
		for (unsigned int i = 0; i < pauselayer->getChildren()->count(); ++i) {
			auto obj = static_cast<CCNode*>(pauselayer->getChildren()->objectAtIndex(i));
			obj->setVisible(false);
		}
		pauselayer->setTouchEnabled(false);
	}
};

class $modify(PlayerObject) {
	void playerDestroyed(bool p0) {
		if (GameManager::get()->m_playLayer) {
			static_cast<CoolerPlayLayer*>(GameManager::get()->m_playLayer)->coolerPauseGame(false);

			CREATE_TOMATO_ANIM(auto anim, 2.5f, [](tomato::Animation* self) {
				log::info("toilet");
				self->unschedule(schedule_selector(tomato::Animation::beginAnimation));
				
			});
			auto worldPos = this->getParent()->convertToWorldSpace(this->getPosition());

			auto thePos = CCScene::get()->convertToNodeSpace(worldPos);
			anim->setPosition(thePos);
			anim->setScale(9.0f);
			anim->setAnchorPoint({0.5f, 0.38f});
			CCScene::get()->addChild(anim);
		}
	}
};

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		log::debug("Hello from my MenuLayer::init hook! This layer has {} children.", this->getChildrenCount());

		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
			this,
			menu_selector(MyMenuLayer::onMyButton)
		);

		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(myButton);

		myButton->setID("my-button"_spr);

		menu->updateLayout();

		

		

		return true;
	}

	void onMyButton(CCObject*) {
		FLAlertLayer::create("Geode", "Hello from my custom mod!", "OK")->show();
	}

	void onMoreGames(CCObject*) {
		std::vector<std::string> frameNames;
		for (int i = 0; i <= 118; ++i) {
			frameNames.push_back(fmt::format("frame_{:04}.png", i));
		}
		//auto anim = tomato::Animation::create(frameNames, 2.5f);
		//anim->setPosition(CCDirector::get()->getWinSize() / 2);
		//anim->setScale(9.0f);
		//this->addChild(anim);
	}
};