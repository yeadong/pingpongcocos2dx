//
//  Physics2DCocos.cpp
//  pingpong
//
//  Created by Thinh Tran on 2/11/16.
//
//

#include "PhysicsCocos2D.h"

USING_NS_CC;

START_GAME_NS

// PhysicsCocos2DBody

PhysicsCocos2DBody::PhysicsCocos2DBody() {
    
}

PhysicsCocos2DBody::~PhysicsCocos2DBody() {
    
}

void PhysicsCocos2DBody::setDensity(float density) {
    auto shapes = _body->getShapes();
    for (auto shape : shapes) {
        shape->setDensity(density);
    }
}

void PhysicsCocos2DBody::setFriction(float friction){
    auto shapes = _body->getShapes();
    for (auto shape : shapes) {
        shape->setFriction(friction);
    }
}

void PhysicsCocos2DBody::setRestitution(float restitution){
    auto shapes = _body->getShapes();
    for (auto shape : shapes) {
        shape->setRestitution(restitution);
    }
}

void PhysicsCocos2DBody::setMaterial(float density, float friction, float restitution){
    auto shapes = _body->getShapes();
    for (auto shape : shapes) {
        shape->setDensity(density);
        shape->setFriction(friction);
        shape->setRestitution(restitution);
    }
}

void PhysicsCocos2DBody::setGroup(int groupId){
    _body->setGroup(groupId);
}

void PhysicsCocos2DBody::setCategoryBitmask(int bitmask){
    _body->setCategoryBitmask(bitmask);
}

void PhysicsCocos2DBody::setCollisionBitmask(int bitmask){
    _body->setCollisionBitmask(bitmask);
}

void PhysicsCocos2DBody::setContactTestBitmask(int bitmask){
    _body->setContactTestBitmask(bitmask);
}

void PhysicsCocos2DBody::setDynamic(bool isDynamic){
    _body->setDynamic(isDynamic);
}

void PhysicsCocos2DBody::setKinematic(bool isKinematic) {
    // kinematic currently is not supported by cocos2d-x
    _body->setDynamic(isKinematic);
}

void PhysicsCocos2DBody::setGravity(bool inGravity){
    _body->setGravityEnable(inGravity);
}

void PhysicsCocos2DBody::setVelocity(const cocos2d::Vec2 &vel) {
    _body->setVelocity(vel);
}

Vec2 PhysicsCocos2DBody::getVelocity() {
    return _body->getVelocity();
}

void PhysicsCocos2DBody::setPosition(const cocos2d::Vec2 &vel) {
    _bodySprite->setPosition(vel);
}

void PhysicsCocos2DBody::movePosition(const cocos2d::Vec2 &vel) {
    auto prevPos = _bodySprite->getPosition();
    _bodySprite->setPosition(prevPos.x + vel.x, prevPos.y + vel.x);
}

cocos2d::Vec2 PhysicsCocos2DBody::getPosition() {
    return _bodySprite->getPosition();
}

bool PhysicsCocos2DBody::isSupportCCD() {
    return false;
}

void PhysicsCocos2DBody::enableCCD() {
    // do nothing because cocos2dx currently (v3.8) doesn't support continuous collision detection
}

// PhysicsCocos2DWorld

PhysicsCocos2DWorld::PhysicsCocos2DWorld() {
    
}

PhysicsCocos2DWorld::~PhysicsCocos2DWorld() {
    for (auto it = _bodies.begin(); it != _bodies.end(); ++it) {
        auto body = *it;
        SAFE_DELETE_POINTER(body);
    }
}

void PhysicsCocos2DWorld::init(cocos2d::Scene *scene, float gravityX, float gravityY) {
    Physics2DWorld::init(scene, gravityX, gravityY);
    
    _world = scene->getPhysicsWorld();
    _world->setGravity(Vec2(gravityX, gravityY));
}

Physics2DBody* PhysicsCocos2DWorld::addBodyBox(cocos2d::Sprite* sprite,
                                                      const Size& size,
                                                      PhysicsMaterial material) {

    auto physicsBody = PhysicsBody::createBox(size, material);
    physicsBody->setDynamic(false);
    sprite->setPhysicsBody(physicsBody);
    
    PhysicsCocos2DBody *pBody = new PhysicsCocos2DBody();
    pBody->setBody(physicsBody);
    pBody->setSprite(sprite);
    
    _bodies.push_back(pBody);
    return pBody;
}

Physics2DBody* PhysicsCocos2DWorld::addBodyCircle(cocos2d::Sprite* sprite,
                                               float radius,
                                               PhysicsMaterial material) {
    
    auto physicsBody = PhysicsBody::createCircle(radius, material);
    physicsBody->setDynamic(false);
    sprite->setPhysicsBody(physicsBody);
    
    PhysicsCocos2DBody *pBody = new PhysicsCocos2DBody();
    pBody->setBody(physicsBody);
    pBody->setSprite(sprite);
    
    _bodies.push_back(pBody);
    return pBody;
}

Physics2DBody* PhysicsCocos2DWorld::addBody(cocos2d::Sprite* sprite, const std::string &bodyName) {
    auto loader = PhysicsShapeCache::getInstance();
    auto body = loader->createBodyWithName(bodyName);
    
    sprite->setPhysicsBody(body);
    PhysicsCocos2DBody *pBody = new PhysicsCocos2DBody();
    pBody->setBody(body);
    pBody->setSprite(sprite);
    
    _bodies.push_back(pBody);
    return pBody;
}

void PhysicsCocos2DWorld::removeBody(Physics2DBody *body) {
    body->getSprite()->removeFromParentAndCleanup(true);
}

void PhysicsCocos2DWorld::loadBodies(const std::string &plist) {
    auto loader = PhysicsShapeCache::getInstance();
    loader->addShapesWithFile(plist);
}

void PhysicsCocos2DWorld::registerContactListener(Physics2DContactListener* listener) {
    
}

void PhysicsCocos2DWorld::drawDebug() {
    _world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
}

END_GAME_NS