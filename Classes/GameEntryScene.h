#ifndef __GAME_ENTRY_SCENE_H__
#define __GAME_ENTRY_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameEntryScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameEntryScene);


    void gotoFlappyBird(Ref* pSender);
};

#endif // __GAME_ENTRY_SCENE_H__
