//
// Created by Administrator on 2017/11/25 0025.
//

#include "GameLayer.h"
#include "../collision.h"

#define LOG_TAG "FlappyBirdGameLayer_TAG"

bool GameLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    //获取可见区域尺寸
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //获取可见区域原点坐标
    Point origin = Director::getInstance()->getVisibleOrigin();

    // 添加精灵
    mBackground = Sprite::create("fp/vp.jpg");
    mBackground->setAnchorPoint(Point(0, 0));
    mBackground->setPosition(
            Point(origin.x, origin.y + visibleSize.height - mBackground->getContentSize().height));
    this->addChild(mBackground, 0);
    CCLOG("%s, bg.w=%f, bg.h=%f", LOG_TAG, mBackground->getContentSize().width,
          mBackground->getContentSize().height);

    mBird = initBird();
    Size backgroundSize = mBackground->getContentSize();
    //添加小鸟精灵，并播放动画
    mBird->setPosition(
            Point(origin.x + visibleSize.width / 2, origin.y + backgroundSize.height * 4 / 5));
    this->addChild(mBird, 0);
    mBird->runAction(RepeatForever::create(mAnimAc));

    // 添加地板
    mFloor = initFloor();
    mFloor->setAnchorPoint(Point(0, 0));
    mFloor->setPosition(Point(origin.x, origin.y));
    this->addChild(mFloor);
    Size floorSize = mFloor->getContentSize();
    auto moveTo1 = MoveTo::create(1, Vec2(-120, 0));
    auto moveTo2 = MoveTo::create(1, Vec2(0, 0));
    mFloor->runAction(RepeatForever::create(
            Sequence::createWithTwoActions(moveTo1, moveTo2)
    ));

    //创建一个单点触摸监听
    auto listener = EventListenerTouchOneByOne::create();
    //设置下传触摸
    listener->setSwallowTouches(true);
    //开始触摸时回调onTouchBegan方法
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    //添加到监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    CCLOG("%s, init", LOG_TAG);
    return true;
}

Sprite *GameLayer::initFloor() {
    Sprite *sprite = Sprite::create("fp/floor1.png");
    return sprite;
}

Sprite *GameLayer::initBird() {
    Sprite *bird = Sprite::create();

    SpriteFrameCache *sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("fp/bird.plist", "fp/birdP.png");
    //动画图片的名称
    std::string animBird[3] =
            {
                    "bird1.png",
                    "bird2.png",
                    "bird3.png"
            };

    //创建存放动画帧的向量
    Vector<SpriteFrame *> animFrames;
    //获取动画帧
    animFrames.pushBack(sfc->getSpriteFrameByName(animBird[0]));
    animFrames.pushBack(sfc->getSpriteFrameByName(animBird[1]));
    animFrames.pushBack(sfc->getSpriteFrameByName(animBird[2]));
    //创建动画对象，从帧向量产生动画，间隔为0.1秒
    Animation *anim = Animation::createWithSpriteFrames(animFrames, 0.1f);
    //创建动画动作对象
    mAnimAc = Animate::create(anim);
    //因为暂时不用，保持引用，防止被自动释放
    mAnimAc->retain();

    return bird;
}

void GameLayer::initColumn1() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Size winSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    CCLOG("%s, visibleSize.width=%.2f, visibleSize.height=%.2f, "
                  "winSize.width=%.2f, winSize.height=%.2f,"
                  "origin.x=%.2f, origin.y=%.2f",
          LOG_TAG, visibleSize.width, visibleSize.height, winSize.width, winSize.height, origin.x,
          origin.y);
    //获取背景尺寸大小
    Size backSize = mBackground->getContentSize();
//    CCLOG("%s, backSize.width=%.2f, backSize.height=%.2f", LOG_TAG, backSize.width,
//          backSize.height);
    //获取地面尺寸大小
    Size floorSize = mFloor->getContentSize();
//    CCLOG("%s, floorSize.width=%.2f, floorSize.height=%.2f", LOG_TAG, floorSize.width,
//          floorSize.height);

    int capInset = 2;
    int height1 = randomColumn();
    Sprite *columnNode1 = Sprite::create("fp/column1.png");
    Size sSize = columnNode1->getContentSize();
    mColumnUnder1 = Scale9Sprite::create();
//    mColumnUnder1->updateWithBatchNode(columnNode1, Rect(0, 0, 96, 400), false, Rect(0, 30, 96, 400));
    mColumnUnder1->updateWithSprite(columnNode1, Rect(0, 0, sSize.width, sSize.height), false,
                                    Rect(capInset, capInset, sSize.width - capInset * 2,
                                         sSize.height - capInset * 2));
    mColumnUnder1->setAnchorPoint(Point(0, 0));
    mColumnUnder1->setContentSize(Size(COLUMN_WIDTH, height1));
    mColumnUnder1->setColor(Color3B(128, 0, 0));
    mColumnUnder1->setPosition(Point(origin.x + visibleSize.width, floorSize.height));

    int height2 = (int) (visibleSize.height - floorSize.height - height1 - COLUMN_GAP);
    Sprite *columnNode2 = Sprite::create("fp/column2.png");
    mColumnOn1 = Scale9Sprite::create();
    sSize = columnNode2->getContentSize();

    mColumnOn1->updateWithSprite(columnNode2, Rect(0, 0, sSize.width, sSize.height),
                                 false, Rect(capInset, capInset, sSize.width - capInset * 2,
                                             sSize.height - capInset * 2));
    mColumnOn1->setAnchorPoint(Point(0, 0));
    mColumnOn1->setContentSize(Size(Size(COLUMN_WIDTH, height2)));
    mColumnOn1->setPosition(
            Point(origin.x + visibleSize.width, floorSize.height + height1 + COLUMN_GAP));

    this->addChild(mColumnUnder1, 0);
    this->addChild(mColumnOn1, 0);
    mColumnUnder1->runAction(RepeatForever::create(MoveBy::create(COLUMN_SPEED, Point(-25, 0))));
    mColumnOn1->runAction(RepeatForever::create(MoveBy::create(COLUMN_SPEED, Point(-25, 0))));

}

void GameLayer::initColumn2() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //获取背景尺寸大小
    Size backSize = mBackground->getContentSize();
    //获取地面尺寸大小
    Size floorSize = mFloor->getContentSize();

    int capInset = 2;
    int height1 = randomColumn();
    Point columnUnder1Size = mColumnUnder1->getPosition();
    Sprite *columnNode1 = Sprite::create("fp/column1.png");
    Size sSize = columnNode1->getContentSize();
    mColumnUnder2 = Scale9Sprite::create();
//    mColumnUnder1->updateWithBatchNode(columnNode1, Rect(0, 0, 96, 400), false, Rect(0, 30, 96, 400));
    mColumnUnder2->updateWithSprite(columnNode1, Rect(0, 0, sSize.width, sSize.height), false,
                                    Rect(capInset, capInset, sSize.width - capInset * 2,
                                         sSize.height - capInset * 2));
    mColumnUnder2->setAnchorPoint(Point(0, 0));
    mColumnUnder2->setContentSize(Size(COLUMN_WIDTH, height1));
    mColumnUnder2->setPosition(Point(columnUnder1Size.x + COLUMN_SPACING, floorSize.height));

    int height2 = (int) (visibleSize.height - floorSize.height - height1 - COLUMN_GAP);
    Sprite *columnNode2 = Sprite::create("fp/column2.png");
    mColumnOn2 = Scale9Sprite::create();
    sSize = columnNode2->getContentSize();

    mColumnOn2->updateWithSprite(columnNode2, Rect(0, 0, sSize.width, sSize.height),
                                 false, Rect(capInset, capInset, sSize.width - capInset * 2,
                                             sSize.height - capInset * 2));
    mColumnOn2->setAnchorPoint(Point(0, 0));
    mColumnOn2->setContentSize(Size(Size(COLUMN_WIDTH, height2)));
    mColumnOn2->setPosition(
            Point(columnUnder1Size.x + COLUMN_SPACING, floorSize.height + height1 + COLUMN_GAP));

    this->addChild(mColumnUnder2, 0);
    this->addChild(mColumnOn2, 0);
    mColumnUnder2->runAction(RepeatForever::create(MoveBy::create(COLUMN_SPEED, Point(-25, 0))));
    mColumnOn2->runAction(RepeatForever::create(MoveBy::create(COLUMN_SPEED, Point(-25, 0))));
}

int GameLayer::random() {
    srand((unsigned) time(NULL));
    int number = rand() % 5 + 1;
    return number;
}

int GameLayer::randomColumn(int min, int max) {
    std::random_device rd;
    int number = rd() % (max - min + 1) + min;
    CCLOG("%s, randomColumn = %d", LOG_TAG, number);
    return number;
}

bool GameLayer::onTouchBegan(Touch *touch, Event *event) {
    Point birdPosition = mBird->getPosition();
    CCLOG("%s, %s", LOG_TAG, __FUNCTION__);

    if (mReadyFlag) {
        startGame();
        mReadyFlag = false;
    }

    if(mRunFlag) {
        auto action = Spawn::createWithTwoActions(
                MoveTo::create(0.2, Vec2(birdPosition.x, birdPosition.y + BIRD_FLY_SPEED)),
                RotateTo::create(0, -30));
        mBird->stopAllActions();
        mBird->runAction(RepeatForever::create(mAnimAc));
        mBird->runAction(
                Sequence::create(
                        CallFunc::create(CC_CALLBACK_0(GameLayer::setRunFlag1, this)),
                        action,
                        DelayTime::create(0.05 ),
                        CallFunc::create(CC_CALLBACK_0(GameLayer::setRunFlag2, this)),
                        RotateTo::create(2.0, 90),
                        NULL
                ));
    }

    return true;

}

void GameLayer::startGame() {

    if (!mRunFlag) {
        // start game
        mRunFlag = true;
        initColumn1();
        initColumn2();

        birdDrop();

        //设置定时回调指定方法干活
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->schedule(schedule_selector(GameLayer::updateColumn), this, 0.05, false);
        scheduler->schedule(schedule_selector(GameLayer::updateBird), this, 0.05, false);

    } else {
        // already started
        CCLOG("%s, has already started", LOG_TAG);
    }

}

void GameLayer::birdDrop() {
    Vec2 birdPosition = mBird->getPosition();
    Size floorSize = mFloor->getContentSize();
    float time = 10;
    auto createAction = MoveTo::create(time, Point(birdPosition.x, floorSize.height));
    mBird->runAction(
            Sequence::create(createAction,
                             CallFunc::create(CC_CALLBACK_0(GameLayer::onAfterBirdDropped, this)),
                             NULL));
}

void GameLayer::updateColumn(float delta) {

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 columnPosition1 = mColumnUnder1->getPosition();
    Vec2 columnPosition2 = mColumnUnder2->getPosition();
    Size columnSize = mColumnUnder1->getContentSize();

//    CCLOG("%s, columnPos.x=%f, columnPos.x=%f", LOG_TAG, columnPosition1.x, columnPosition2.y);

    if (columnPosition1.x <= origin.x - columnSize.width) {
        removeChild(mColumnUnder1);
        removeChild(mColumnOn1);
        initColumn1();
    }

    if (columnPosition2.x < origin.x - columnSize.width) {
        removeChild(mColumnUnder2);
        removeChild(mColumnOn2);
        initColumn2();
    }
}

void GameLayer::updateBird(float delta) {
    if (mRunFlag) {
        birdDrop();
    }

    //获取小鸟当前位置
    Vec2 birdPosition = mBird->getPosition();
    //获取小鸟尺寸大小
    Size birdSize = mBird->getContentSize();
    //获取地面位置
    Vec2 floorPos = mFloor->getPosition();
    //获取地面尺寸大小
    Size floorSize = mFloor->getContentSize();

    bool checkFloor = collision(birdPosition.x, birdPosition.y, birdPosition.x + birdSize.width,
                                birdPosition.y + birdSize.height,
                                floorPos.x, floorPos.y, floorPos.x + floorSize.width,
                                floorPos.y + floorSize.height
    );
    CCLOG("%s, checkFloor=%s", LOG_TAG, checkFloor ? "true" : "false");

    if (checkFloor) {
        gameOver();
    }
}

void GameLayer::onAfterBirdDropped() {
    //CCLOG("%s, onAfterBirdDropped", LOG_TAG);

}

void GameLayer::gameOver() {
    CCLOG("%s, gameOver 11", LOG_TAG);
    mRunFlag = false;
    mReadyFlag = true;
    Point birdPosition = mBird->getPosition();
    Size birdSize = mBird->getContentSize();
    Size floorSize = mFloor->getContentSize();

    mFloor->stopAllActions();
    mColumnOn1->stopAllActions();
    mColumnUnder1->stopAllActions();
    mColumnUnder2->stopAllActions();
    mColumnOn2->stopAllActions();
    mBird->stopAllActions();
    mBird->runAction(Sequence::create(Spawn::createWithTwoActions(
            MoveTo::create(0.2, Point(birdPosition.x, floorSize.height + birdSize.width / 2)),
            RotateTo::create(0.2, 90)), NULL));

    CCLOG("%s, gameOver 22", LOG_TAG);
}

void GameLayer::setRunFlag1() {

}
void GameLayer::setRunFlag2() {

}

