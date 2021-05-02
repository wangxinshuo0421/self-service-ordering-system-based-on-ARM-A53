#ifndef __LISTFRESH__
#define __LISTFRESH__

#include "font.h"
#include <stdio.h>
#include <string.h>

//listPosition = -1 绘制表格

void FreshList(int foodId,int foodNum,int color,int listPosition,int money){
	char buf[30];
	switch (foodId){
		case 10:
			sprintf(buf,"西红柿天鹅     %2d  %d",foodNum,money);
			break;
		case 11:
			sprintf(buf,"血橙胡萝卜汁   %2d  %d",foodNum,money);
			break;
		case 12:
			sprintf(buf,"冰糖阿胶燕窝   %2d  %d",foodNum,money);
			break;
		case 13:
			sprintf(buf,"花胶牛奶冻     %2d  %d",foodNum,money);
			break;
		case 14:
			sprintf(buf,"木瓜炖奶       %2d  %d",foodNum,money);
			break;
		case 15:
			sprintf(buf,"银耳雪蛤羹     %2d  %d",foodNum,money);
			break;
		case 16:
			sprintf(buf,"糟溜鱼片       %2d  %d",foodNum,money);
			break;
		case 17:
			sprintf(buf,"日式香煎三文鱼 %2d  %d",foodNum,money);
			break;
		case 18:
			sprintf(buf,"红焖带鱼       %2d  %d",foodNum,money);
			break;
		case 19:
			sprintf(buf,"果仁菠菜       %2d  %d",foodNum,money);
			break;
		case 20:
			sprintf(buf,"腐竹鱼头煲     %2d  %d",foodNum,money);
			break;
		case 21:
			sprintf(buf,"红烧排骨       %2d  %d",foodNum,money);
			break;
		case 22:
			sprintf(buf,"草莓牛奶布丁   %2d  %d",foodNum,money);
			break;
		case 23:
			sprintf(buf,"孜然排骨       %2d  %d",foodNum,money);
			break;
		case 24:
			sprintf(buf,"麻辣香锅       %2d  %d",foodNum,money);
			break;			
		default:
			break;
	}
	if(listPosition == -1){//绘制表格
		Display_characterX(0,60,"菜品          数量 单价",black,1);
		sprintf(buf,"总价:           %3d元",money);
	    Display_characterX(0,395,buf,black,1);
	}else{
		Display_characterX(0,listPosition*30+80,buf,black,1);
	}

}

#endif
