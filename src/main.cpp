#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;



// Why this shit has to be long? i have no fucking idea
class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        this->runAction(CCSequence::create(
            CCDelayTime::create(0.0f),
            CCCallFunc::create(this, callfunc_selector(MyMenuLayer::swapButtons)),
            nullptr
        ));
        return true;
    }
    void swapButtons() {
        CCMenuItemSpriteExtra* playBtn = nullptr;
        CCMenuItemSpriteExtra* creatorBtn = nullptr;
        auto children = this->getChildren();
        for (int i = 0; i < children->count(); i++) {
            auto child = static_cast<CCNode*>(children->objectAtIndex(i));
            if (auto menu = typeinfo_cast<CCMenu*>(child)) {
                auto menuChildren = menu->getChildren();
                for (int j = 0; j < menuChildren->count(); j++) {
                    if (auto btn = typeinfo_cast<CCMenuItemSpriteExtra*>(menuChildren->objectAtIndex(j))) {
                        if (btn->m_pfnSelector == menu_selector(MenuLayer::onPlay)) {
                            playBtn = btn;
                        }
                        else if (btn->m_pfnSelector == menu_selector(MenuLayer::onCreator)) {
                            creatorBtn = btn;
                        }
                    }
                }
            }
        }
        if (playBtn && creatorBtn) {
            auto textureQuality = CCDirector::sharedDirector()->getLoadedTextureQuality();
            CCSize playSize, creatorSize;
            switch (textureQuality) {
                case kTextureQualityLow:
                    playSize = CCSize(68, 68);
                    creatorSize = CCSize(106, 106);
                    break;
                case kTextureQualityMedium:
                    playSize = CCSize(134, 134);
                    creatorSize = CCSize(211, 209);
                    break;
                case kTextureQualityHigh:
                    playSize = CCSize(266, 266);
                    creatorSize = CCSize(418, 418);
                    break;
                default:
                    playSize = CCSize(134, 134);
                    creatorSize = CCSize(211, 209);
                    break;
            }
            auto newPlaySprite = CCSprite::createWithSpriteFrameName("GJ_playBtn_001.png");
            auto newCreatorSprite = CCSprite::createWithSpriteFrameName("GJ_creatorBtn_001.png");
            newPlaySprite->setContentSize(playSize);
            newCreatorSprite->setContentSize(creatorSize);
            auto playPos = playBtn->getPosition();
            auto creatorPos = creatorBtn->getPosition();
            playBtn->setPosition(creatorPos);
            creatorBtn->setPosition(playPos);
            playBtn->setNormalImage(newCreatorSprite);
            creatorBtn->setNormalImage(newPlaySprite);
            playBtn->activate();
            playBtn->m_pfnSelector = menu_selector(MenuLayer::onCreator);
            creatorBtn->m_pfnSelector = menu_selector(MenuLayer::onPlay);
        }
    }
};
