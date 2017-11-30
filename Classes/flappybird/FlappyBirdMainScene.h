//
// Created by Administrator on 2017/11/25 0025.
//

#ifndef PROJ_ANDROID_STUDIO_FLAPPYBIRDMAINSCENE_H
#define PROJ_ANDROID_STUDIO_FLAPPYBIRDMAINSCENE_H

#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

class FlappyBirdMainScene : public cocos2d::Scene
{

private:
    GameLayer* mGameLayer;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(FlappyBirdMainScene);



};


#endif //PROJ_ANDROID_STUDIO_FLAPPYBIRDMAINSCENE_H
