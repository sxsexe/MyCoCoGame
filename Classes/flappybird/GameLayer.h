//
// Created by Administrator on 2017/11/25 0025.
//

#ifndef PROJ_ANDROID_STUDIO_GAMELAYER_H
#define PROJ_ANDROID_STUDIO_GAMELAYER_H

#include "cocos2d.h"

USING_NS_CC;

class GameLayer : public Layer
{
public:
    // 小鸟精灵
    Sprite * mBird;
    // 动画动作数组
    Animate* animAc;

    //声明背景精灵
    Sprite *mBackground;

private:
    Sprite* initBird();

public:
    // 初始化GameLayer
    virtual bool init();
    // 用宏声明一个create方法，并将该对象加入AutoReleasePool
    CREATE_FUNC(GameLayer);
};


#endif //PROJ_ANDROID_STUDIO_GAMELAYER_H
