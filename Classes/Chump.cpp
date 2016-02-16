//
//  Chump.cpp
//  pingpong
//
//  Created by Thinh Tran on 1/13/16.
//
//

#include "Chump.h"
#include "Physics.h"

USING_NS_CC;


void Chump::init(cocos2d::Sprite *sprite, cocos2d::Sprite *topEdge, cocos2d::Sprite *bottomEdge, bool flipped) {
    _topEdge = topEdge;
    _botEdge = bottomEdge;
    
    setSprite(sprite);
    std::string bodyName = flipped? "chump3_flip" : "chump3";

    auto world = Physics::getWorld2D();
    physicsBody = world->addBody(sprite, bodyName);
    physicsBody->setKinematic(true);
    
    registerTouchEvents();
    
    auto limitMoveRange = [this] (float dt) {
        // Limit top and bot movings
        auto chumpRect = getSprite()->getBoundingBox();
        auto topRect = _topEdge->getBoundingBox();
        auto botRect = _botEdge->getBoundingBox();
        float dy = 0;
        
        if (topRect.intersectsRect(chumpRect)) {
            dy -= chumpRect.getMaxY() - topRect.getMinY();
        } else if (botRect.intersectsRect(chumpRect)) {
            dy += botRect.getMaxY() - chumpRect.getMinY();
        }
        
        dy *= getSprite()->getScale();
        
        physicsBody->movePosition(cocos2d::Vec2(0, dy));
    };
    
    sprite->schedule(limitMoveRange, 0.016f, "limitChumpMoveRange");
}

void Chump::registerTouchEvents() {
    auto listener = EventListenerTouchOneByOne::create();
    auto sprite = getSprite();
    
    listener->onTouchBegan = [] (Touch* touch, Event* event) {
        return true;
    };
    
    listener->onTouchMoved = [this] (Touch* touch, Event* event) {
        auto target = event->getCurrentTarget();
        auto prevPos = physicsBody->getPosition();
        auto dy = touch->getDelta().y;

        // Same scale as chump sprite
        dy *= target->getScaleY();
        
        physicsBody->movePosition(cocos2d::Vec2(0, dy)); 
    };
    

    auto eventDispatcher = sprite->getEventDispatcher();
    
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite);
}