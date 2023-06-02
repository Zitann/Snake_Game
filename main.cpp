#include "snake.h"
#include "food.h"
#include "map.h"
#include "mdata.h"
#include <easyx.h>

#include <iostream>
#include <thread>


// 定义地图的大小
#define MAP_WIDTH 62
#define MAP_HEIGHT 42

// 定义像素的大小
#define PIXEL_SIZE 15


// 定义颜色
#define FOOD RED
#define SNAKE_HEAD WHITE

// 定义蛇的移动方向
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// 定义蛇头的初始位置
#define SNAKE_HEAD_X 20
#define SNAKE_HEAD_Y 20

using namespace std;

// 游戏初始参数
int score = 0;
int speed = 120;
int direction = RIGHT;

void drewCell(int x, int y, int color); // 画一个像素
void delCell(int x, int y); // 删除一个像素
void up();  //监控上键
void down();  //监控下键
void mleft();  //监控左键
void mright();  //监控右键
void esc();  //监控esc键

int main()
{
    //初始化窗口
    initgraph(MAP_WIDTH * PIXEL_SIZE, MAP_HEIGHT * PIXEL_SIZE);
    map m(MAP_WIDTH, MAP_HEIGHT);

    //创建线程，用于监听键盘输入
    thread t1(up);
    thread t2(down);
    thread t3(mleft);
    thread t4(mright);
    thread t5(esc);

    //进入开始界面
    m.start();

    closegraph();
    return 0;
}

void drewCell(int x, int y, int color)
{
    setfillcolor(color);
    fillrectangle(x * PIXEL_SIZE, y * PIXEL_SIZE, (x + 1) * PIXEL_SIZE, (y + 1) * PIXEL_SIZE);

}

void delCell(int x, int y)
{
    setfillcolor(BLACK);
    clearrectangle(x * PIXEL_SIZE, y * PIXEL_SIZE, (x + 1) * PIXEL_SIZE, (y + 1) * PIXEL_SIZE);
}

void up()
{
    while (true)
    {
        if(GetAsyncKeyState(VK_UP)&0x8000)
        {
            if(direction != DOWN)
            {
                direction = UP;
            }
        }
    }
}

void down()
{
    while(true)
    {
        if(GetAsyncKeyState(VK_DOWN)&0x8000)
        {
            if(direction != UP)
            {
                direction = DOWN;
            }
        }
    }
}

void mleft()
{
    while (true)
    {
        if(GetAsyncKeyState(VK_LEFT)&0x8000)
        {
            if(direction != RIGHT)
            {
                direction = LEFT;
            }
        }
    }
}

void mright()
{
    while (true)
    {
        if(GetAsyncKeyState(VK_RIGHT)&0x8000)
        {
            if(direction != LEFT)
            {
                direction = RIGHT;
            }
        }
    }
}

void esc()
{
    while (true)
    {
        if(GetAsyncKeyState(VK_ESCAPE)&0x8000)
        {
            exit(0);
        }
    }
}