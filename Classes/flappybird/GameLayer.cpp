//
// Created by Administrator on 2017/11/25 0025.
//

#include "GameLayer.h"

#define LOG_TAG "FlappyBirdGameLayer_TAG"

bool GameLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }

    //获取可见区域尺寸
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //获取可见区域原点坐标
    Point origin = Director::getInstance()->getVisibleOrigin();

    mBackground = Sprite::create("fp/night.png");
    mBackground->setAnchorPoint(Point(0, 0));
    mBackground->setPosition(Point(origin.x, origin.y + visibleSize.height - mBackground->getContentSize().height));
    this->addChild(mBackground, 0);

    mBird = initBird();
    Size backgroundSize = mBackground->getContentSize();
    //设置精灵位置
    mBird->setPosition(Point(140 + origin.x, origin.y + backgroundSize.height/2));
    this->addChild(mBird, 2);
    mBird->runAction(RepeatForever::create(animAc));

    CCLOG("%s, init", LOG_TAG);
    return true;
}

Sprite* GameLayer::initBird()
{
    Sprite* bird = Sprite::create();

    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("fp/bird.plist", "fp/birdP.png");
    //动画图片的名称
    std::string animBird[3] =
    {
            "bird1.png",
            "bird2.png",
            "bird3.png"
    };

    //创建存放动画帧的向量
    Vector<SpriteFrame*> animFrames;
    //获取动画帧
    animFrames.pushBack(sfc->getSpriteFrameByName(animBird[0]));
    animFrames.pushBack(sfc->getSpriteFrameByName(animBird[1]));
    animFrames.pushBack(sfc->getSpriteFrameByName(animBird[2]));
    //创建动画对象，从帧向量产生动画，间隔为0.1秒
    Animation *anim = Animation::createWithSpriteFrames(animFrames, 0.1f);
    //创建动画动作对象
    animAc = Animate::create(anim);
    //因为暂时不用，保持引用，防止被自动释放
    animAc->retain();

    return bird;
}
