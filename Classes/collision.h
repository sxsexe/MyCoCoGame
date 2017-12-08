//
// Created by Administrator on 2017/11/28 0028.
//

#ifndef PROJ_ANDROID_STUDIO_COLLISION_H
#define PROJ_ANDROID_STUDIO_COLLISION_H

#include <math.h>
#include <platform/CCStdC.h>
#include <base/CCConsole.h>

/**
 *
 * @param srcLBx 左下角坐标.x
 * @param srcLBy 左下角左边.y
 * @param srcRTx 右上角.x
 * @param srcRTy 右上角.y
 * @param targetLBx
 * @param targetLBy
 * @param targetRTx
 * @param targetRTy
 * @return
 */
static bool collision(double srcLBx, double srcLBy, double srcRTx, double srcRTy,
                      double targetLBx, double targetLBy, double targetRTx, double targetRTy) {
    if((srcLBx > targetRTx) || srcRTx < targetLBx) {
//        CCLOG("CollisionCheck 111 \n");
        return false;
    } else {
        if(srcLBy > targetRTy || srcRTy < targetLBy) {
//            CCLOG("CollisionCheck 22 \n");
            return false;
        }
    }

//    CCLOG("CollisionCheck 33 \n");
    CCLOG("CollisionCheck srcLBx=%f, srcLBy=%f, srcRTx=%f, srcRTy=%f,"
                  "targetLBx=%f, targetLBy=%f, targetRTx=%f, targetRTy=%f",
          srcLBx, srcLBy, srcRTx, srcRTy, targetLBx, targetLBy, targetRTx, targetRTy);

    return true;

}



#endif //PROJ_ANDROID_STUDIO_COLLISION_H
