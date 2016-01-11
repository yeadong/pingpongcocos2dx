#include "SplashScene.h"
#include "MainMenuScene.h"
#include "EnterNameScene.h"
#include "GameSettings.h"
#include "Player.h"

LoadingBar* loadingBar;

// on "init" you need to initialize your instance
bool Splash::init(std::string csbFile)
{
    BaseScene::init(csbFile);
    loadingBar = (LoadingBar *)_rootNode->getChildByName("loadingBar");
    this->schedule(schedule_selector(Splash::updateProgress), 0.01f);
    
    // Init game settings
    auto settings = GameSettings::getInstance();
    
    // Init player
    auto player = Player::getInstance();
    settings->loadPlayer(player);

    return true;
}

void Splash::nextScene(float dt) {
    if (GameSettings::getInstance()->isFirstTime()) {
        Director::getInstance()->replaceScene(EnterName::createScene());
        return;
    }
    Director::getInstance()->replaceScene(MainMenu::createScene());
}

float counter = 0;
void Splash::updateProgress(float dt) {
    counter++;
    if (counter > 100)
    {
        unschedule(schedule_selector(Splash::updateProgress));
        this->scheduleOnce(schedule_selector(Splash::nextScene), 0.05f);
    }
    loadingBar->setPercent(counter);
}



