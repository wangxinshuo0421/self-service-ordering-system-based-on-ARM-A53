#ifndef __TASK__
#define __TASK__

#include "MyLib.h"
#include "draw.h"
#include "keyboard.h"
#include "orderKey.h"
#include "Food.h"
#include "user.h"
#include "font.h"
#include "listFresh.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/input.h>


 //默认模式 0->主页; 1->注册;  2->登录; 
int modeIndex(){
    if(firstInModeFlag){
        firstInModeFlag = 0;
        displayBmpPicture(0,0,"picture/index.bmp");
    }
    if(touchEvent.type == EV_ABS) {  //绝对事件（触摸屏)
        if(touchEvent.code == ABS_X) {//x轴事件
            x = touchEvent.value;
        }else if(touchEvent.code == ABS_Y){
            y = touchEvent.value;
        }else if(touchEvent.code == ABS_PRESSURE){
            if(touchEvent.value == 0){
                if(loginAbove<y && y<loginBelow){
                    if(registerLeft<x && x<registerRight){
                        //默认模式 0->主页; 1->注册;  2->登录; 
                        mode = 1;
                    }else if(loginLeft<x && x<loginRight){
                        mode = 2;
                    }
                }
                printf("松开  x = %d; y = %d\n",x,y);
            }else{
                printf("按下 x = %d; y = %d\n",x,y);
            }
        }
    }
}

int modeRegister(){
    int keyBoardInput = noInput;
    if(firstInModeFlag){        //第一次进入，刷新背景
        userNameInput = 0;
        userPasswordInput = 0;
        firstInModeFlag = 0;
        displayBmpPicture(0,0,"picture/register.bmp");
        NameInputFlag = 0;
        loginPageFreshFlag = 1;
        PasswordInputFlag = 0;
    }
    keyBoardInput = getNumKeyInput();
    if(keyBoardInput == returnButton){
        printf("return button\n");
        mode = 0;
        NameInputFlag = 0;
        PasswordInputFlag = 0;
    }
    if(keyBoardInput == confirmButton){
        printf("confirm button\n");
        mode = 3;
        PasswordInputFlag = 0;
        NameInputFlag = 0;
    }
    if(keyBoardInput == userIdButton){
        printf("user id button\n");
        NameInputFlag = 1;
        PasswordInputFlag = 0;
    }
    if(keyBoardInput == passwordButton){
        printf("password button\n");
        PasswordInputFlag = 1;
        NameInputFlag = 0;
    }
    if(keyBoardInput == confirmButton){
        printf("confirm Button\n");
        if(userPasswordInput < 1000 || userNameInput < 1000 || userNameInput > 9999 || userPasswordInput > 9999){
            displayBmpPicture(0,0,"picture/error.bmp");
            printf("error!!\n");
            sleep(1);
            mode = 0;
        }else{
            writeUserInFile(userNameInput,userPasswordInput);
            userHead = initUserFile();
            printf("success register\nname = %d;password = %d\n",userNameInput,userPasswordInput);
            displayBmpPicture(0,0,"picture/success.bmp");
            mode = 0;
        }
        
    }
    if(NameInputFlag && 0<=keyBoardInput && keyBoardInput<=9){    //输入用户名
        loginPageFreshFlag = 1;
        userNameInput = keyBoardInput + userNameInput*10;
        printf("userName = %5d; keyboardInput = %d\n",userNameInput,keyBoardInput);
    }
    if(PasswordInputFlag && 0<=keyBoardInput && keyBoardInput<=9){     //输入密码
        loginPageFreshFlag = 1;
        userPasswordInput = keyBoardInput + userPasswordInput*10;
        printf("password = %5d\n",userPasswordInput);
    }
    if(PasswordInputFlag && keyBoardInput == backOffButton){
        loginPageFreshFlag = 1;
        userPasswordInput = userPasswordInput/10;
        printf("password = %5d\n",userPasswordInput);
    }
    if(NameInputFlag && keyBoardInput == backOffButton){
        loginPageFreshFlag = 1;
        userNameInput = userNameInput/10;
        printf("user name = %5d\n",userNameInput);
    }
    if(loginPageFreshFlag){
        loginPageFreshFlag = 0;
        char buf[30];
        int userDigit = 0, passwordDigit = 0, userTemp = userNameInput, passwordTemp = userPasswordInput;
        while(userTemp%10) {
            userDigit++;
            userTemp = userTemp/10;
        }
        while(passwordTemp%10){
            passwordDigit++;
            passwordTemp = passwordTemp/10;
        }
        switch (userDigit)
        {
        case 0:
            displayColorBlock(390,40,780,96,white);
            Display_characterX(390,35,"****",black,5);
            break;
        case 1:
            displayColorBlock(390,40,780,96,white);
            sprintf(buf,"%1d***",userNameInput);
            Display_characterX(390,35,buf,black,5);
            break;
        case 2:
            displayColorBlock(390,40,780,96,white);
            sprintf(buf,"%2d**",userNameInput);
            Display_characterX(390,35,buf,black,5);
            break;
        case 3:
            displayColorBlock(390,40,780,96,white);
            sprintf(buf,"%3d*",userNameInput);
            Display_characterX(390,35,buf,black,5);
            break;
        case 4:
            displayColorBlock(390,40,780,96,white);
            sprintf(buf,"%4d",userNameInput);
            Display_characterX(390,35,buf,black,5);
            break;
        default:
            break;
        }
        switch (passwordDigit)
        {
        case 0:
            displayColorBlock(390,120,780,185,white);
            Display_characterX(390,120,"****",black,5);
            break;
        case 1:
            displayColorBlock(390,120,780,185,white);
            sprintf(buf,"%1d***",userPasswordInput);
            Display_characterX(390,120,buf,black,5);
            break;
        case 2:
            displayColorBlock(390,120,780,185,white);
            sprintf(buf,"%2d**",userPasswordInput);
            Display_characterX(390,120,buf,black,5);
            break;
        case 3:
            displayColorBlock(390,120,780,185,white);
            sprintf(buf,"%3d*",userPasswordInput);
            Display_characterX(390,120,buf,black,5);
            break;
        case 4:
            displayColorBlock(390,120,780,185,white);
            sprintf(buf,"%4d",userPasswordInput);
            Display_characterX(390,120,buf,black,5);
            break;
        default:
            break;
        }
    }
}

int modeLogin(){
    int keyBoardInput = noInput,passFlag = 0;
    if(firstInModeFlag){        //第一次进入，刷新背景
        passFlag = 0;
        userNameInput = 0;
        userPasswordInput = 0;
        loginPageFreshFlag = 1;
        firstInModeFlag = 0;
        displayBmpPicture(0,0,"picture/login.bmp");
        NameInputFlag = 0;
        PasswordInputFlag = 0;
    }
    keyBoardInput = getNumKeyInput();
    if(keyBoardInput == returnButton){
        printf("return button\n");
        mode = 0;
        NameInputFlag = 0;
        PasswordInputFlag = 0;
    }
    if(keyBoardInput == confirmButton){
        printf("confirm button\n");
        mode = 3;
        PasswordInputFlag = 0;
        NameInputFlag = 0;
    }
    if(keyBoardInput == userIdButton){
        printf("user id button\n");
        NameInputFlag = 1;
        PasswordInputFlag = 0;
    }
    if(keyBoardInput == passwordButton){
        printf("password button\n");
        PasswordInputFlag = 1;
        NameInputFlag = 0;
    }
    if(keyBoardInput == confirmButton){
        printf("confirm Button\n");
        if(userNameInput == 0 || userPasswordInput == 0){
            displayBmpPicture(0,0,"picture/error.bmp");
            printf("error!!\n");
            sleep(1);
            mode = 0;
        }
        userLink = userHead;
        while (userLink->next != NULL){
            userLink = userLink -> next;
            printf("read user name = %d;password = %d\n",userLink->userName,userLink->userPassword);
            printf("input name = %d;  input password = %d\n",userNameInput,userPasswordInput);
            if(userLink->userName == userNameInput && userLink->userPassword == userPasswordInput){
                userLink->isSelected = 1;
                passFlag = 1;
            }
        }
        if(passFlag){   //密码正确
            displayBmpPicture(0,0,"picture/success.bmp");
            printf("success in\n");
            sleep(1);
            mode = 3;
            return 1;
        }else{
            displayBmpPicture(0,0,"picture/error.bmp");
            printf("error in\n");
            sleep(1);
            mode = 0;
            return 0;
        }
    }
    if(NameInputFlag && 0<=keyBoardInput && keyBoardInput<=9){    //输入用户名
        loginPageFreshFlag = 1;
        userNameInput = keyBoardInput + userNameInput*10;
        printf("userName = %5d; keyboardInput = %d\n",userNameInput,keyBoardInput);
    }
    if(PasswordInputFlag && 0<=keyBoardInput && keyBoardInput<=9){     //输入密码
        loginPageFreshFlag = 1;
        userPasswordInput = keyBoardInput + userPasswordInput*10;
        printf("password = %5d\n",userPasswordInput);
    }
    if(PasswordInputFlag && keyBoardInput == backOffButton){
        loginPageFreshFlag = 1;
        userPasswordInput = userPasswordInput/10;
        printf("password = %5d\n",userPasswordInput);
    }
    if(NameInputFlag && keyBoardInput == backOffButton){
        loginPageFreshFlag = 1;
        userNameInput = userNameInput/10;
        printf("user name = %5d\n",userNameInput);
    }
    if(loginPageFreshFlag){
        loginPageFreshFlag = 0;
        char buf[30];
        int userDigit = 0, passwordDigit = 0, userTemp = userNameInput, passwordTemp = userPasswordInput;
        while(userTemp%10) {
            userDigit++;
            userTemp = userTemp/10;
        }
        while(passwordTemp%10){
            passwordDigit++;
            passwordTemp = passwordTemp/10;
        }
        switch (userDigit)
        {
        case 0:
            displayColorBlock(390,40,780,96,white);
            Display_characterX(390,35,"****",black,5);
            break;
        case 1:
            displayColorBlock(390,40,780,96,white);
            sprintf(buf,"%1d***",userNameInput);
            Display_characterX(390,35,buf,black,5);
            break;
        case 2:
            displayColorBlock(390,40,780,96,white);
            sprintf(buf,"%2d**",userNameInput);
            Display_characterX(390,35,buf,black,5);
            break;
        case 3:
            displayColorBlock(390,40,780,96,white);
            sprintf(buf,"%3d*",userNameInput);
            Display_characterX(390,35,buf,black,5);
            break;
        case 4:
            displayColorBlock(390,40,780,96,white);
            sprintf(buf,"%4d",userNameInput);
            Display_characterX(390,35,buf,black,5);
            break;
        default:
            break;
        }
        switch (passwordDigit)
        {
        case 0:
            displayColorBlock(390,120,780,185,white);
            Display_characterX(390,120,"****",black,5);
            break;
        case 1:
            displayColorBlock(390,120,780,185,white);
            sprintf(buf,"%1d***",userPasswordInput);
            Display_characterX(390,120,buf,black,5);
            break;
        case 2:
            displayColorBlock(390,120,780,185,white);
            sprintf(buf,"%2d**",userPasswordInput);
            Display_characterX(390,120,buf,black,5);
            break;
        case 3:
            displayColorBlock(390,120,780,185,white);
            sprintf(buf,"%3d*",userPasswordInput);
            Display_characterX(390,120,buf,black,5);
            break;
        case 4:
            displayColorBlock(390,120,780,185,white);
            sprintf(buf,"%4d",userPasswordInput);
            Display_characterX(390,120,buf,black,5);
            break;
        default:
            break;
        }
    }
}

/**struct Food{
    int foodIdentify;
    int attribute;
    int pageRowPosition;
    int pageColumePosition;
    int orderNum;
    struct Food* next;
};*/

int initOrderPage(){
    char foodBmpName[30],strBuf[30];
    if(firstInModeFlag){        //第一次进入，刷新背景
        firstInModeFlag = 0;
        //清空点餐记录
        foodLink = head;
        while (foodLink->next != NULL){
            foodLink = foodLink -> next;
            foodLink->orderNum = 0;
        }
        displayBmpPicture(0,0,"picture/menu.bmp");
    }
    if(firstInMenuPage){        //第一次进入本页菜单
        firstInMenuPage = 0;
        orderRefreshFlag = 1;
        displayBmpPicture(0,0,"picture/menu.bmp");
        displayColorBlock(200,15,200+10,15+10,white);
        displayColorBlock(330,15,330+10,15+10,white);
        displayColorBlock(480,15,480+10,15+10,white);
        displayColorBlock(630,15,630+10,15+10,white);
        switch (menuPage)
        {
        case 1:
            displayColorBlock(200,15,200+10,15+10,green);
            break;
        case 2:
            displayColorBlock(330,15,330+10,15+10,green);
            break;
        case 3:
            displayColorBlock(480,15,480+10,15+10,green);
            break;
        case 4:
            displayColorBlock(630,15,630+10,15+10,green);
            break;
        default:
            break;
        }
        foodLink = head;
        while (foodLink->next != NULL){
            foodLink = foodLink -> next;
            if(foodLink -> attribute == menuPage){      //该食物为本页面所属
                sprintf(foodBmpName,"picture/%d.bmp",foodLink->foodIdentify);
                displayBmpPicture((foodLink->pageColumePosition)*200,(foodLink->pageRowPosition - 1)*200 + 65,foodBmpName);
                displayColorBlock((foodLink->pageColumePosition)*200,(foodLink->pageRowPosition - 1)*200 + 65,\
                                (foodLink->pageColumePosition)*200+10,(foodLink->pageRowPosition - 1)*200 + 65+10,white);           
            }
        }
    }
    if(orderRefreshFlag == 1){      //页面需要刷新
        int listPosition = 0;
        int money = 0;
        orderRefreshFlag = 0;
        foodLink = head;
        displayColorBlock(0,56,185,420,white);  
        while (foodLink->next != NULL){
            foodLink = foodLink -> next;
            if(foodLink -> attribute == menuPage){      //该食物为本页面所属
                if(foodLink -> orderNum>0){
                    displayColorBlock((foodLink->pageColumePosition)*200,(foodLink->pageRowPosition - 1)*200 + 65,\
                                (foodLink->pageColumePosition)*200+10,(foodLink->pageRowPosition - 1)*200 + 65+10,green);  
                }else{
                    displayColorBlock((foodLink->pageColumePosition)*200,(foodLink->pageRowPosition - 1)*200 + 65,\
                                (foodLink->pageColumePosition)*200+10,(foodLink->pageRowPosition - 1)*200 + 65+10,white);  
                }
            }
            if(foodLink->orderNum>0){           //本菜品被点
                money = money + (foodLink->orderNum)*(foodLink->money);
                displayColorBlock(0,395,185,420,white);
                FreshList(foodLink->foodIdentify,foodLink->orderNum,black,listPosition++,foodLink->money);
                FreshList(0,0,black,-1,money);
            }
        }
    }
}

int modeOrder(){
    int orderInput;
    int foodId,foodNum,foodPosition;
    
    initOrderPage();
    
    orderInput = getOrderInput();

    if(orderInput != wrongInput){   //有效输入
        orderRefreshFlag = 1;
        printf("order input : %d\n",orderInput);
        switch (orderInput)
        {
        case submitButton:  //提交订单
            mode = 4;
            submitFlag = 1;
            printf("subumit\n");
            break;
        case UnsubmitButton:    //返回
            mode = 2;
            printf("unsubmit\n");
            break;
        case leftSlip:
            printf("left slip\n");
            menuPage++;
            if(menuPage>4) menuPage = 4;
            printf("menu page:%d\n",menuPage);
            firstInMenuPage = 1;
            break;
        case rightSlip:
            printf("right slip\n");
            menuPage--;
            if(menuPage<1) menuPage = 1;
            printf("menu page:%d\n",menuPage);
            firstInMenuPage = 1;
            break;
        default:        //菜单操作
            printf("position Input: %d\n",orderInput);
            if(1<=orderInput && orderInput<=6){     //加菜功能
                foodLink = head;
                while (foodLink->next != NULL){
                    foodLink = foodLink -> next;
                    if(foodLink -> attribute == menuPage){      //该食物为本页面所属
                        foodPosition = ((foodLink -> pageRowPosition) - 1) *3 + foodLink -> pageColumePosition; //计算食物编码
                        if(foodPosition == orderInput){
                            foodLink->orderNum = foodLink->orderNum + 1;
                            printf("food = %d orderNum = %d\n",foodLink->foodIdentify,foodLink->orderNum);
                        }
                    }
                }
            }else{      //减菜功能
                foodLink = head;
                while (foodLink->next != NULL){
                    foodLink = foodLink -> next;
                    if(foodLink -> attribute == menuPage){      //该食物为本页面所属
                        foodPosition = ((foodLink -> pageRowPosition) - 1) *3 + foodLink -> pageColumePosition; //计算食物编码
                        if((foodPosition + 6 ) == orderInput){
                            foodLink->orderNum = foodLink->orderNum - 1;
                            if (foodLink->orderNum < 0)     foodLink->orderNum = 0;
                            printf("food = %d orderNum = %d\n",foodLink->foodIdentify,foodLink->orderNum);
                        }
                    }
                }
            }
            break;
        }
    }
}

int modeSubmit(){
    if(firstInModeFlag){        //第一次进入，刷新背景
        firstInModeFlag = 0;
        displayBmpPicture(0,0,"picture/wait.bmp");
    }
    if(sendFlag){
        sendFlag = 0;
        submitFlag = 0;
        displayBmpPicture(0,0,"picture/success.bmp");
        mode = 0;
    }
}

 //默认模式 0->主页; 1->注册;  2->登录; 
int taskSchedule(){
    if(mode != lastMode){
        firstInModeFlag = 1;
        lastMode = mode;
    }
    switch (mode)
    {
    case 0:
        modeIndex();
        break;
    case 1:
        modeRegister();
        break;
    case 2:
        modeLogin();
        break;
    case 3:
        modeOrder();
        break;
    case 4:
        modeSubmit();
    default:
        break;
    }
}

#endif
