#ifndef __ORDERKEY__
#define __ORDERKEY__

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/input.h>
#include "MyLib.h"

#define submitButton        -1
#define UnsubmitButton      -2
#define wrongInput          -3
#define leftSlip            -4
#define rightSlip           -5
#define position1           1
#define position2           2
#define position3           3
#define position4           4
#define position5           5
#define position6           6
#define longPosition1       7
#define longPosition2       8
#define longPosition3       9
#define longPosition4       10
#define longPosition5       11
#define longPosition6       12



#define position1Above      65
#define position1Below      225
#define position1Left       200
#define position1Right      360
#define position2Left       400
#define position2Right      560
#define position3Left       600
#define position3Right      760

#define position4Above      265
#define position4Below      425
#define position4Left       200
#define position4Right      360
#define position5Left       400
#define position5Right      560
#define position6Left       600
#define position6Right      760

#define submitAbove     430
#define submitBelow     480
#define submitLeft      0
#define submitRight     90
#define unSubmitLeft    100
#define unSubmitRight   180

int getOrderInput(void){
    if(pressFlag == 1)  pressTime++;
    if(touchEvent.type == EV_ABS) {  //绝对事件（触摸屏）
        if(touchEvent.code == ABS_X) {//x轴事件
            x = touchEvent.value;
        }else if(touchEvent.code == ABS_Y){
            y = touchEvent.value;
        }else if(touchEvent.code == ABS_PRESSURE){
            if(touchEvent.value == 0){
                pressFlag = 0;
                printf("松开\n");
                printf("presstime: %d \n",pressTime);
                if(pressTime<12000000){   //  短按  || 滑动
                    pressTime = 0;
                    releaseX = x;
                    releaseY = y;
                    if(releaseX>pressX && (releaseX - pressX)>100){    //右划
                        releaseX = 0;
                        releaseY = 0;
                        pressX = 0;
                        pressY = 0;
                        return rightSlip;
                    }else if(pressX>releaseX && (pressX - releaseX)>100){   //左滑
                        releaseX = 0;
                        releaseY = 0;
                        pressX = 0;
                        pressY = 0;
                        return leftSlip;
                    }
                    if(position1Above<y && y<position1Below && position1Left<x && x<position1Right) return position1;
                    if(position1Above<y && y<position1Below && position2Left<x && x<position2Right) return position2;
                    if(position1Above<y && y<position1Below && position3Left<x && x<position3Right) return position3;
                    if(position4Above<y && y<position4Below && position4Left<x && x<position4Right) return position4;
                    if(position4Above<y && y<position4Below && position5Left<x && x<position5Right) return position5;
                    if(position4Above<y && y<position4Below && position6Left<x && x<position6Right) return position6;
                    if(submitAbove<y && y<submitBelow && submitLeft<x && x<submitRight) return submitButton;
                    if(submitAbove<y && y<submitBelow && unSubmitLeft<x && x<unSubmitRight) return UnsubmitButton;
                }else{      //长按
                    pressTime = 0;
                    if(position1Above<y && y<position1Below && position1Left<x && x<position1Right) return longPosition1;
                    if(position1Above<y && y<position1Below && position2Left<x && x<position2Right) return longPosition2;
                    if(position1Above<y && y<position1Below && position3Left<x && x<position3Right) return longPosition3;
                    if(position4Above<y && y<position4Below && position4Left<x && x<position4Right) return longPosition4;
                    if(position4Above<y && y<position4Below && position5Left<x && x<position5Right) return longPosition5;
                    if(position4Above<y && y<position4Below && position6Left<x && x<position6Right) return longPosition6;
                }
            }else{
                pressFlag = 1;
                pressX = x;
                pressY = y;
                printf("按下\n");
            }
        }
    }
    return wrongInput;
}

#endif
