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
    this->setKeyboardEnabled(true);

    switchState(GAME_PREPARE);

    return true;
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
    CCLOG("%s onKeyReleased", LOG_TAG);
    if(keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE){
        CCLOG("%s KEY_BACKSPACE", LOG_TAG);
    }
}

void GameLayer::initTouchListener() {
    //创建一个单点触摸监听
    auto listener = EventListenerTouchOneByOne::create();
    //设置下传触摸
    listener->setSwallowTouches(true);
    //开始触摸时回调onTouchBegan方法
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    //添加到监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameLayer::initFloor() {
    if(mFloor != NULL) {
        CCLOG("mFloor has been inited");
        return;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //获取可见区域原点坐标
    Point origin = Director::getInstance()->getVisibleOrigin();
    mFloor = Sprite::create("fp/floor1.png");
//    mFloor->setContentSize(Size(visibleSize.width * 4, mFloor->getContentSize().height));
    mFloor->setAnchorPoint(Point(0, 0));

    CCLOG("%s, initFloor visibleSize.width=%.2f, visibleSize.height=%.2f, "
                  "origin.x =%.2f, origin.y = %.2f, mFloor.width=%.2f, mFloor.height=%.2f",
          LOG_TAG, visibleSize.width, visibleSize.height,
          origin.x, origin.y, mFloor->getContentSize().width, mFloor->getContentSize().height);

    mFloor->setPosition(Point(origin.x, origin.y));
    this->addChild(mFloor);
    Size floorSize = mFloor->getContentSize();
    auto moveTo1 = MoveTo::create(1, Vec2(-120, 0));
    auto moveTo2 = MoveTo::create(1, Vec2(0, 0));
    mFloor->runAction(RepeatForever::create(
            Sequence::createWithTwoActions(moveTo1, moveTo2)
    ));
}

void GameLayer::initGameOverSprite() {

}

void GameLayer::initPrepareSprite() {
    if(mPreparedBird != NULL) {
        CCLOG("mPreparedBird has been inited");
        return;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    mPreparedBird = Sprite::create("fp/readyBird.png");
//    mPreparedBird->setAnchorPoint(Point(0, 0));
    mPreparedBird->setPosition(
            Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(mPreparedBird);
}

void GameLayer::initBackground() {
    if(mBackground != NULL) {
        CCLOG("mBackground has been inited");
        return;
    }
    //获取可见区域尺寸
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //获取可见区域原点坐标
    Point origin = Director::getInstance()->getVisibleOrigin();

    mBackground = Sprite::create("fp/vp.jpg");
    mBackground->setAnchorPoint(Point(0, 0));

    CCLOG("%s, initBackground visibleSize.width=%.2f, visibleSize.height=%.2f, "
                  "origin.x =%.2f, origin.y = %.2f, mBackground.width=%.2f, mBackground.height=%.2f",
          LOG_TAG, visibleSize.width, visibleSize.height,
          origin.x, origin.y, mBackground->getContentSize().width,
          mBackground->getContentSize().height);

    mBackground->setPosition(
            Point(origin.x, origin.y + visibleSize.height - mBackground->getContentSize().height));
    this->addChild(mBackground, 0);
}

void GameLayer::initBird() {
    if(mBird != NULL) {
        CCLOG("mBird has been inited");
        return;
    }
    mBird = Sprite::create();

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

    Point origin = Director::getInstance()->getVisibleOrigin();
    Size backgroundSize = mBackground->getContentSize();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //添加小鸟精灵，并播放动画
    mBird->setPosition(
            Point(origin.x + visibleSize.width / 2, origin.y + backgroundSize.height * 4 / 5));
    this->addChild(mBird, 10);
    mBird->runAction(RepeatForever::create(mAnimAc));
}

void GameLayer::initColumn1() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Size winSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    CCLOG("%s, initColumn1 visibleSize.width=%.2f, visibleSize.height=%.2f, "
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

std::string GameLayer::getEnumString(GameStateEnum state) {

    switch (state) {
        case GAME_PREPARE:
            return std::string("GAME_PREPARE");
        case GAME_RUNNING:
            return std::string("GAME_RUNNING");
        case GAME_OVER:
            return std::string("GAME_OVER");
        default:
            return std::string("UnKnown State");
    }

}

bool GameLayer::onTouchBegan(Touch *touch, Event *event) {
    CCLOG("%s, onTouchBegan", LOG_TAG);
    if(mCurrentState == GAME_PREPARE) {

        switchState(GAME_RUNNING);

    } else if(mCurrentState == GAME_RUNNING) {
        if(mBird == NULL) {
            return true;
        }
        Point birdPosition = mBird->getPosition();
        auto action = Spawn::createWithTwoActions(
                MoveTo::create(0.2, Vec2(birdPosition.x, birdPosition.y + BIRD_FLY_SPEED)),
                RotateTo::create(0, -30));
        mBird->stopAllActions();
        mBird->runAction(RepeatForever::create(mAnimAc));
        mBird->runAction(
                Sequence::create(
                        CallFunc::create(CC_CALLBACK_0(GameLayer::setRunFlag1, this)),
                        action,
                        DelayTime::create(0.05),
                        CallFunc::create(CC_CALLBACK_0(GameLayer::setRunFlag2, this)),
                        RotateTo::create(2.0, 90),
                        NULL
                ));

    }  else if(mCurrentState == GAME_OVER) {
        // FIXME replay
    }

    return true;

}

void GameLayer::startGame() {
    birdDrop();
    //设置定时回调指定方法干活
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->schedule(schedule_selector(GameLayer::updateColumn), this, 0.05, false);
    scheduler->schedule(schedule_selector(GameLayer::updateBird), this, 0.05, false);
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
    if (mCurrentState == GAME_RUNNING) {
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
//    CCLOG("%s, checkFloor=%s", LOG_TAG, checkFloor ? "true" : "false");

    if (checkFloor) {
        switchState(GAME_OVER);
    }
}

void GameLayer::onAfterBirdDropped() {
    //CCLOG("%s, onAfterBirdDropped", LOG_TAG);

}

void GameLayer::onGameOver() {
    CCLOG("%s, onGameOver 11", LOG_TAG);
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

    CCLOG("%s, onGameOver 22", LOG_TAG);
}

void GameLayer::setRunFlag1() {

}

void GameLayer::setRunFlag2() {

}

void GameLayer::onStateEnter(GameStateEnum newState) {
    CCLOG("%s, onStateEnter newState=%s, currentState=%s", LOG_TAG, getEnumString(newState).c_str(),
          getEnumString(mCurrentState).c_str());
    if (newState == mCurrentState) {
        // ignore
        CCLOG("%s, onStateEnter same state, Ignore!!!", LOG_TAG);
        return;
    }
    mCurrentState = newState;
    switch (newState) {
        case GAME_PREPARE: {
            initBackground();
            initFloor();
            initPrepareSprite();
            initTouchListener();
        }
            break;
        case GAME_RUNNING: {
            initBird();
            initColumn1();
            initColumn2();
            startGame();
        }
            break;
        case GAME_OVER: {
            //显示Replay界面
            initGameOverSprite();
        }
            break;
        default:
            CCLOG("%s, should never run here", LOG_TAG);
            break;
    }
}


void GameLayer::onStateExit(GameStateEnum state) {
    CCLOG("%s, onStateExit state=%s", LOG_TAG, getEnumString(state).c_str());
    switch (state) {
        case GAME_PREPARE: {
            removeChild(mPreparedBird, true);
        }
            break;
        case GAME_RUNNING: {
            onGameOver();
        }
            break;
        case GAME_OVER:{

        }

            break;
        default:
            break;
    }
}

void GameLayer::switchState(GameStateEnum newState) {
    GameStateEnum lastState = mCurrentState;
    onStateExit(lastState);
    onStateEnter(newState);

}




