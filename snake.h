//
// Created by jzita on 2023/5/26.
//

#ifndef SNAKE_GAME_SNAKE_H
#define SNAKE_GAME_SNAKE_H
#include "food.h"

class snake
{
private:
    int x;
    int y;
    snake* next;
public:
    snake();
    void move(int direction, food* f);
    bool isEatSelf();        //判断是否吃到自己
    bool isHitWall();        //判断是否撞墙
    bool isEatFood(food* f);     //判断是否吃到食物
    void speedUp();      //加速
    void speedDown();        //减速
    int getX();
    int getY();
    snake* getNext();
    void setX(int x);
    void setY(int y);
    void setNext(snake* next);
};

#endif //SNAKE_GAME_SNAKE_H
