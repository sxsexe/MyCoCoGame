//
// Created by Administrator on 2017/11/28 0028.
//

#ifndef PROJ_ANDROID_STUDIO_COLLISION_H
#define PROJ_ANDROID_STUDIO_COLLISION_H

#include <math.h>
#include <platform/CCStdC.h>
#include <base/CCConsole.h>

static bool collision(double srcLTx, double srcLTy, double srcRBx, double srcRBy,
                      double targetLTx, double targetLTy, double targetRBx, double targetRBy) {
    if((srcLTx > targetRBx) || srcRBx < targetLTx) {
//        CCLOG("CollisionCheck 111 \n");
        return false;
    } else {
        if(srcLTy > targetRBy || srcRBy < targetLTy) {
//            CCLOG("CollisionCheck 22 \n");
            return false;
        }
    }

//    CCLOG("CollisionCheck 33 \n");
//    CCLOG("CollisionCheck srcLTx=%f, srcLTy=%f, srcRBx=%f, srcRBy=%f,"
//                  "targetLTx=%f, targetLTy=%f, targetRBx=%f, targetRBy=%f",
//          srcLTx, srcLTy, srcRBx, srcRBy, targetLTx, targetLTy, targetRBx, targetRBy);

    return true;

}



#endif //PROJ_ANDROID_STUDIO_COLLISION_H
