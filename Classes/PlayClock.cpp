//
//  PlayClock.cpp
//  pingpong
//
//  Created by Thinh Tran on 1/13/16.
//
//

#include "PlayClock.h"

START_GAME_NS

PlayClock::PlayClock()
: totalTime(0)
, _paused(false) {
    
}

PlayClock::~PlayClock() {
    
}

void PlayClock::init(float speed) {
    GameObject::init("playclock");
    auto sprite = cocos2d::Sprite::create();
    sprite->setName("playclock");
    setSprite(sprite);
    _speed = speed;
}

void PlayClock::start() {
    _paused = false;
}

void PlayClock::pause() {
    _paused = true;
}

void PlayClock::resume() {
    _paused = false;
}

void PlayClock::reset() {
    totalTime = 0;
}


void PlayClock::update(float deltaTime) {
    if (!_paused) {
        totalTime += deltaTime;
    }
}

END_GAME_NS