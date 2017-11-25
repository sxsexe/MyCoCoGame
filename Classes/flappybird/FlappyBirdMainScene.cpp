//
// Created by Administrator on 2017/11/25 0025.
//

#include "FlappyBirdMainScene.h"

#define LOG_TAG "FlappyBirdMainScene_TAG"

bool FlappyBirdMainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    mGameLayer = GameLayer::create();
    this->addChild(mGameLayer);

    CCLOG("%s, init", LOG_TAG);

    return true;
}

Scene* FlappyBirdMainScene::createScene()
{

    return FlappyBirdMainScene::create();
}

