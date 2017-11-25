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

    // 添加精灵
    mBackground = Sprite::create("fp/vplants_001.jpg");
    mBackground->setAnchorPoint(Point(0, 0));
    mBackground->setPosition(Point(origin.x, origin.y + visibleSize.height - mBackground->getContentSize().height));
    this->addChild(mBackground, 0);
    CCLOG("%s, bg.w=%f, bg.h=%f", LOG_TAG, mBackground->getContentSize().width, mBackground->getContentSize().height);

    mBird = initBird();
    Size backgroundSize = mBackground->getContentSize();
    //添加小鸟精灵，并播放动画
    mBird->setPosition(Point(140 + origin.x, origin.y + backgroundSize.height / 3));
    this->addChild(mBird, 0);
    mBird->runAction(RepeatForever::create(animAc));

    // 添加地板
    mFloor = initFloor();
    mFloor->setAnchorPoint(Point(0, 0));
    mFloor->setPosition(Point(origin.x, origin.y));
    this->addChild(mFloor);
    Size floorSize = mFloor->getContentSize();
    mFloor->runAction(RepeatForever::create(
            Sequence::create(
                    MoveTo::create(0.5, Point(-120, 0)),
                    MoveTo::create(0.5, Point(0, 0))
            )
    ));

    initColumn1();

    CCLOG("%s, init", LOG_TAG);
    return true;
}

Sprite* GameLayer::initFloor()
{
    Sprite* sprite = Sprite::create("fp/floor1.png");
    return sprite;
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

void GameLayer::initColumn1() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //获取背景尺寸大小
    Size backSize = mBackground->getContentSize();
    //获取地面尺寸大小
    Size floorSize = mFloor->getContentSize();
    int i = random();

    int height1 =  400 / i;
    Sprite* columnNode1 = Sprite::create("fp/column1.png");
    mColumnUnder1 = Scale9Sprite::create();
//    mColumnUnder1->updateWithBatchNode(columnNode1, Rect(0, 0, 96, 400), false, Rect(0, 30, 96, 400));
    mColumnUnder1->updateWithSprite(columnNode1, Rect(0, 0, 96, 400), false, Rect(0, 0, 96, 400));
    mColumnUnder1->setAnchorPoint(Point(0, 0));
    mColumnUnder1->setContentSize(Size(96, height1));
    mColumnUnder1->setPosition(Point(visibleSize.width, floorSize.height));
    CCLOG("%s, mColumnUnder1.height=%d, position.x=%.2f, position.y=%.2f ", LOG_TAG, height1,
          visibleSize.width, floorSize.height);

    int height2 = backSize.height - height1 - 196;
    SpriteBatchNode* columnNode2 = SpriteBatchNode::create("fp/column2.png");
    mColumnOn1 = Scale9Sprite::create();
    mColumnOn1->updateWithBatchNode(columnNode2, Rect(0, 0, 96, 400), false, Rect(0, 0, 96, 370));
    mColumnOn1->setAnchorPoint(Point(0, 0));
    mColumnOn1->setContentSize(Size(96, height2));
    mColumnOn1->setPosition(Point(visibleSize.width, visibleSize.height - height2));

    this->addChild(mColumnUnder1, 0);
//    this->addChild(mColumnOn1, 0);
    mColumnUnder1->runAction(RepeatForever::create(MoveBy::create(3, Point(-25, 0))));
//    mColumnOn1->runAction(RepeatForever::create(MoveBy::create(3, Point(-25, 0))));

}

void GameLayer::initColumn2() {

}

int GameLayer::random() {
    srand((unsigned)time(NULL));
    int number = rand() % 5 + 1;
    return number;
}
