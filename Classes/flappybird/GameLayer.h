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
    int randomColumn(int min = COLUMN_MIN_H, int max = COLUMN_MAX_H);

    bool onTouchBegan(Touch* touch, Event* event);

private:
    const int COLUMN_WIDTH = 24;
    const int COLUMN_GAP = 60;
    static const int COLUMN_MIN_H = 60;
    static const int COLUMN_MAX_H = 200;
    const int COLUMN_SPACING = 120;
    const float COLUMN_SPEED = 0.8;

public:
    // 初始化GameLayer
    virtual bool init();
    // 用宏声明一个create方法，并将该对象加入AutoReleasePool
    CREATE_FUNC(GameLayer);
};


#endif //PROJ_ANDROID_STUDIO_GAMELAYER_H
