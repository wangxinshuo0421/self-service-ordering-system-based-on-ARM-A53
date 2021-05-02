#ifndef __KEYBOARD__
#define __KEYBOARD__

#include "MyLib.h"


#define returnButtonAbove   120
#define returnButtonBelow   200
#define returnButtonLeft    20
#define returnButtonRight   190

#define backOffAbove    250
#define backOffBelow    320
#define backOffLeft     600
#define backOffRight    750

#define confirmAbove    360
#define confirmBelow    450
#define confirmLeft     590
#define confirmRight    750

#define Num1Above   240
#define Num1Below   350
#define Num6Above   350
#define Num6Below   470

#define Num1Left    0
#define Num1Right   100
#define Num2Left    105
#define Num2Right   205
#define Num3Left    210
#define Num3Right   310
#define Num4Left    315
#define Num4Right   415
#define Num5Left    420
#define Num5Right   520

#define Num6Left    0
#define Num6Right   100
#define Num7Left    105
#define Num7Right   205
#define Num8Left    210
#define Num8Right   310
#define Num9Left    315
#define Num9Right   415
#define Num0Left    420
#define Num0Right   520

#define passwordLeft    250
#define passwordRight   800
#define passwordAbove   120
#define passwordBelow   190
#define userIdAbove       20
#define userIdBelow       100

#define noInput         -10
#define userIdButton    -5
#define passwordButton  -4    
#define returnButton    -3
#define backOffButton   -2
#define confirmButton   -1
#define num0 0
#define num1 1
#define num2 2
#define num3 3
#define num4 4
#define num5 5
#define num6 6
#define num7 7
#define num8 8
#define num9 9

 
/**
 * returnButton : -3
 * backOff : -2
 * confirm : -1
 * noInput : -10
 * 0 - 9 : 0-9
 * */

int getNumKeyInput(void){
    if(touchEvent.type == EV_ABS) {  //绝对事件（触摸屏）
        if(touchEvent.code == ABS_X) {//x轴事件
            x = touchEvent.value;
        }else if(touchEvent.code == ABS_Y){
            y = touchEvent.value;
        }else if(touchEvent.code == ABS_PRESSURE){
            if(touchEvent.value == 0){
                if(returnButtonAbove<y && y<returnButtonBelow && returnButtonLeft<x && x<registerRight){
                    return  returnButton;
                }
                if(backOffAbove<y && y<backOffBelow && backOffLeft<x && x<backOffRight){
                    return backOffButton;
                }
                if(confirmAbove<y && y<confirmBelow  && confirmLeft<x && x<confirmRight){
                    return confirmButton;
                }
                if(passwordAbove<y && y<passwordBelow && passwordLeft<x && x<passwordRight){
                    return passwordButton;
                }
                if(userIdAbove<y && y<userIdBelow && passwordLeft<x && x<passwordRight){
                    return userIdButton;
                }
                if(Num1Above<y && y<Num1Below){
                    if(Num1Left<x && x<Num1Right)
                        return num1;
                    if(Num2Left<x && x<Num2Right)
                        return num2;
                    if(Num3Left<x && x<Num3Right)
                        return num3;
                    if(Num4Left<x && x<Num4Right)
                        return num4;
                    if(Num5Left<x && x<Num5Right)
                        return num5;
                }else if(Num6Above<y && y<Num6Below){
                    if(Num6Left<x && x<Num6Right)
                        return num6;
                    if(Num7Left<x && x<Num7Right)
                        return num7;
                    if(Num8Left<x && x<Num8Right)
                        return num8;
                    if(Num9Left<x && x<Num9Right)
                        return num9;
                    if(Num0Left<x && x<Num0Right)
                        return num0;
                }
                printf("松开  x = %d; y = %d\n",x,y);
            }else{
                printf("按下 x = %d; y = %d\n",x,y);
            }
        }
    }
    return noInput;
}

#endif