#ifndef __MYLIB__
#define __MYLIB__

#include "Food.h"
#include "user.h"

// touch.h
#define touchFile "/dev/input/event0"
#define LCD "/dev/fb0"
#define backgroundBmp "picture/background.bmp"
#define LCDSize 800*480
#define LCDLength 800
#define LCDWidth 480
#define LCDSizeof 800*480*4

#define registerLeft    100
#define registerRight   330
#define loginLeft       470
#define loginRight      680
#define loginAbove      320
#define loginBelow      400

int red = 0x00FF0000;
int green = 0x0000ff00;
int white = 0x00ffffff;
int black = 0x00000000;
int skyBlue = 0x0087CEEB;
int RoyalBlue = 0x0A4169E1; //	皇家蓝
int Azure = 0x0AF0FFFF;  //蔚蓝色
int DarkVoilet = 0x009400D3;    //	深紫罗兰色	

int touchFilePoint;     //触摸屏文件描述符
struct input_event touchEvent;

int x = 0;
int y = 0;
int pressTime = 0;  //按下后开始自加1，无限循环，直到松开清零
int pressFlag = 0;  //按下置1；抬起置0
int pressX = 0,pressY = 0,releaseX = 0,releaseY = 0;
int isPress = 0;      //0:松开;  1:按下   
int isTouched = 0;     //0:触摸事件未发生 1:触摸事件发生

int mode = 0;       //默认模式 0->主页面; 1->注册;  2->登录;  3->点餐;   4->提交订单
int menuPage = 1;   //  1->热门;  2->健脑;  3->养颜;  4->防辐射;
int firstInMenuPage = 1;     //菜单切换后第一次进入新page的标志位，进入后置零，再次更新mode后置一
int firstInModeFlag = 1;    //模式切换后第一次进入新mode的标志位，进入后置零，再次更新mode后置一
int lastMode = 0;

int orderRefreshFlag = 0;

struct Food* head = NULL, * foodLink = NULL;
struct User* userHead = NULL, * userLink = NULL;

int submitFlag = 0;
int sendFlag = 0;



int photoNum = 1;
int lastPhotoNum = 1;

#endif