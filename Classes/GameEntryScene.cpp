#include "GameEntryScene.h"
#include "SimpleAudioEngine.h"

#define LOG_ATG "GameEntryScene_TAG"

// Menu Item Font Size
const int MENU_ITEM_FONT_SIZE = 20;

Scene* GameEntryScene::createScene()
{
    return GameEntryScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameEntryScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    CCLOG("%s, origin.x=%f, origin.y=%f, visibleSize.w=%f, visibleSize.h=%f", LOG_ATG, origin.x, origin.y,
          visibleSize.width, visibleSize.height);

    // 加入背景
    auto layerColorBG = LayerColor::create(Color4B(180, 170, 160, 255));
    this->addChild(layerColorBG);

    // 增加menu 选择进入的游戏场景
    // Flappy Bird
    MenuItemFont::setFontName("Consolas");
    MenuItemFont::setFontSize(MENU_ITEM_FONT_SIZE);
    auto menuItemFlappyBird = MenuItemFont::create("Flappy Bird", CC_CALLBACK_1(
            GameEntryScene::gotoFlappyBirdScene, this));
    auto menu = Menu::create(menuItemFlappyBird, NULL);
    addChild(menu);
    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height - menuItemFlappyBird->getContentSize().height;
    menu->setPosition(Point(x, 0));

    // menu进入动画
    auto moveBy = MoveBy::create(0.5f, Vec2(0, y));
    auto pBounceInOut = EaseBounceIn::create(moveBy);
    menu->runAction(pBounceInOut);


    //test
//    test();

    return true;
}

void GameEntryScene::gotoFlappyBirdScene(Ref *pSender) {
    CCLOG("%s : gotoFlappyBirdScene ++", LOG_ATG);

    Director::getInstance()->setDepthTest(true);
    mFpMainScene = FlappyBirdMainScene::createScene();
    auto ss = TransitionJumpZoom::create(1, mFpMainScene);
    Director::getInstance()->replaceScene(ss);

    CCLOG("%s : gotoFlappyBirdScene --", LOG_ATG);
}


void GameEntryScene::test() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int a = 2;
    Sprite* sprite = Sprite::create("fp/column2.png");
    Size sSize = sprite->getContentSize();
    Scale9Sprite* s9s1 = Scale9Sprite::create();
    s9s1->updateWithSprite(sprite, Rect(0, 0, sSize.width, sSize.height),
                           false, Rect(a, a, sSize.width-a*2, sSize.height-a*2));

    s9s1->setPosition(Vec2(origin.x + 100, origin.y + 100));
    s9s1->setContentSize(Size(sSize.width, sSize.height*3));
    s9s1->setColor(Color3B(128, 0, 0));

    this->addChild(s9s1);

}