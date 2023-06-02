//
// Created by jzita on 2023/5/26.
//
#include "snake.h"

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

extern int score;
extern int speed;

void drewCell(int x, int y, int color); // 画一个像素
void delCell(int x, int y); // 删除一个像素

snake::snake()
{
    x = SNAKE_HEAD_X;
    y = SNAKE_HEAD_Y;
    next = NULL;
}
void snake::move(int direction, food* f)
{
    //创建p节点，用于保存蛇头的位置
    snake* p = new snake;
    p->x = this->x;
    p->y = this->y;
    switch (direction)
    {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
    }
    drewCell(x, y, SNAKE_HEAD);     //画出移动后蛇头

    //把后面的节点都往前移动一格
    snake* q = this->next;
    while (q != NULL)
    {
        int tempX = q->x;
        int tempY = q->y;
        q->x = p->x;
        q->y = p->y;
        p->x = tempX;
        p->y = tempY;
        q = q->next;
    }

    //判断是否吃到食物，是则在尾部添加一个节点，否则删除尾部节点图像
    if (isEatFood(f))
    {
        f->clear();
        do
        {
            f->setX(rand() % 40+ 1);
            f->setY(rand() % 40 + 1);
        }while (f->getX() == this->getX() && f->getY() == this->getY()||(f->getX()>40||f->getX()<=0)||(f->getY()>40||f->getY()<=0));
        f->draw();
        score += 1;
        if (score % 5 == 0)
        {
            speedUp();
        }
        snake* sn = new snake;
        sn->x = p->x;
        sn->y = p->y;
        sn->next = NULL;
        snake* t = this;
        while(t->next!=NULL)
        {
            t = t->next;
        }
        t->next = sn;
    }
    else
    {
        delCell(p->x, p->y);
    }

}
bool snake::isEatSelf()        //判断是否吃到自己
{
    snake* p = this->next;
    while (p != NULL)
    {
        if (p->x == this->x && p->y == this->y)
        {
            return true;
        }
        p = p->next;
    }
    return false;
}
bool snake::isHitWall()        //判断是否撞墙
{
    if (this->x == 0 || this->x == 41 || this->y == 0 || this->y == 41)
    {
        return true;
    }
    return false;
}
bool snake::isEatFood(food* f)     //判断是否吃到食物
{
    if (this->x == f->x && this->y == f->y)
    {
        return true;
    }
    return false;
}
void snake::speedUp()      //加速
{
    if(speed>40)speed -= 10;
}
void snake::speedDown()        //减速
{
    if(speed<120)speed += 10;
}
int snake::getX()
{
    return x;
}
int snake::getY()
{
    return y;
}
snake* snake::getNext()
{
    return next;
}
void snake::setX(int x)
{
    this->x = x;
}
void snake::setY(int y)
{
    this->y = y;
}
void snake::setNext(snake* next)
{
    this->next = next;
}