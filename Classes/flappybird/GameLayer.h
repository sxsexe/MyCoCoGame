//
// Created by Administrator on 2017/11/25 0025.
//

#ifndef PROJ_ANDROID_STUDIO_GAMELAYER_H
#define PROJ_ANDROID_STUDIO_GAMELAYER_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class GameLayer : public Layer
{
public:
    // 小鸟精灵
    Sprite* mBird;
    // 动画动作数组
    Animate* animAc;

    // 背景精灵
    Sprite* mBackground;
    // floor精灵
    Sprite* mFloor;
    // 柱子精灵
    Scale9Sprite* mColumnUnder1;
    Scale9Sprite* mColumnUnder2;
    Scale9Sprite* mColumnOn1;
    Scale9Sprite* mColumnOn2;


private:
    Sprite* initBird();
    Sprite* initFloor();

    void initColumn1();
    void initColumn2();

    int random();

private:
    const int COLUMN_WIDTH = 96;
    const int COLUMN_GAP = 80;

public:
    // 初始化GameLayer
    virtual bool init();
    // 用宏声明一个create方法，并将该对象加入AutoReleasePool
    CREATE_FUNC(GameLayer);
};


#endif //PROJ_ANDROID_STUDIO_GAMELAYER_H
