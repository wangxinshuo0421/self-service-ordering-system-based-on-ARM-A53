#ifndef __FOOD__
#define __FOOD__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * attribute = 1：热门
 * attribute = 2：健脑益智
 * attribute = 3：养颜
 * attribute = 4：防辐射
 * 
 * 10：西红柿天鹅 attribute = 4
 * 11：血橙胡萝卜汁 attribute = 4
 * 12：冰糖阿胶燕窝 attribute = 3
 * 13：花胶牛奶冻 attribute = 3
 * 14：木瓜炖奶 attribute = 3
 * 15：银耳雪蛤羹 attribute = 3
 * 16：糟溜鱼片 attribute = 2
 * 17：日式香煎三文鱼 attribute = 2
 * 18：红焖带鱼 attribute = 2
 * 19：果仁菠菜 attribute = 2
 * 20：腐竹鱼头煲 attribute =2*/

#define FoodFile "food.txt"

struct Food{
    int foodIdentify;
    int attribute;
    int pageRowPosition;
    int pageColumePosition;
    int orderNum;
    int money;
    struct Food* next;
};

struct Food* initFoodLink(){
    struct Food* head = (struct Food*)malloc(sizeof(struct Food));   //创建头结点
    struct Food* node = NULL,* end = head;
    FILE* filePoint;
    filePoint = fopen(FoodFile,"r");
    int foodIdentify,attribute,pageRowPosition,pageColumePosition,money;

    /*打开文件操作*/
    if(filePoint == NULL){
        printf("fail to open the food file\n");
        return NULL;
    }else{
        printf("open the food file\n");
    }
    while( fscanf(filePoint,"%d %d %d %d %d",&foodIdentify,&money,&attribute,&pageRowPosition,&pageColumePosition) != EOF ) {     //按行读取菜单文件
        node = (struct Food*)malloc(sizeof(struct Food));
        node->foodIdentify = foodIdentify;
        node->money = money;
        node->attribute = attribute;
        node->pageRowPosition = pageRowPosition;
        node->pageColumePosition = pageColumePosition;
        node->orderNum = 0;
        end->next = node;
        end = node;
    }
    end->next = NULL;   //结束创建

    fclose(filePoint);  //关闭文件
    return head;
}
/*
int main(void){
    struct Food* head = NULL;
    head = initFoodLink();
    while (head->next != NULL)
    {
        head = head -> next;
        printf("id:%d;attribute:%d\n",head->foodIdentify,head->attribute);
    }
    
    return 0;
}
*/

#endif

