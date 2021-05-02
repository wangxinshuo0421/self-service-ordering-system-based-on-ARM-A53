#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "draw.h"
#include "touchScreen.h"
#include "task.h"
#include "Food.h"
#include "orderKey.h"
#include "font.h"
#include "client.h"

int main(void)
{
    Init_Font();
    startTouchScreen();
    startClient();
    head = initFoodLink();      //读取菜单文件
    userHead = initUserFile();      //读取用户文件
    foodLink = head;
    while (1){
        taskSchedule();
        //getOrderInput();
    }
    UnInit_Font();
	return 0;
}
