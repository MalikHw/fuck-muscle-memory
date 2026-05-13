#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;



// Why this shit has to be long? i have no fucking idea
class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        this->runAction(CCSequence::create(
            CCDelayTime::create(0.1f),
            CCCallFunc::create(this, callfunc_selector(MyMenuLayer::swapButtons)),
            nullptr
        ));
        return true;
    }
    void swapButtons() {
        auto playBtn = typeinfo_cast<CCMenuItemSpriteExtra*>(this->getChildByID("main-menu")->getChildByID("icon-kit-button"));
        auto creatorBtn = typeinfo_cast<CCMenuItemSpriteExtra*>(this->getChildByID("main-menu")->getChildByID("editor-button"));
        
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
