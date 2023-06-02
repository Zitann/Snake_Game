//
// Created by jzita on 2023/6/2.
//

#ifndef SNAKE_GAME_FOOD_H
#define SNAKE_GAME_FOOD_H

#include <easyx.h>
#include <cstdlib>
#include <ctime>

// 定义地图的大小
#define MAP_WIDTH 62
#define MAP_HEIGHT 42

// 定义像素的大小
#define PIXEL_SIZE 15


// 定义颜色
#define FOOD RED

void drewCell(int x, int y, int color); // 画一个像素

class food
{
private:
    int x;
    int y;
    friend class snake;  //方便蛇类访问
public:
    food()
    {
        srand((unsigned)time(NULL));
        x = rand() % (40) + 1;
        y = rand() % (40) + 1;
    }
    void draw()     //画出食物图像
    {
        drewCell(x, y, FOOD);
    }
    void clear()    //清除食物图像
    {
        drewCell(x, y, WHITE);
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    void setX(int x)
    {
        this->x = x;
    }
    void setY(int y)
    {
        this->y = y;
    }

};


#endif //SNAKE_GAME_FOOD_H
