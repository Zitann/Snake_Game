//
// Created by jzita on 2023/5/26.
//
#include "snake.h"
#include "map.h"
#include "mdata.h"
#include "food.h"
#include <easyx.h>
#include <iostream>

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

extern int score;
extern int speed;
extern int direction;

void delCell(int x, int y); // 删除一个像素

map::map(int w, int h)       //初始化地图大小
{
    width = w;
    height = h;
}
void map::start()        //程序开始界面
{
    //展示标题图片
    IMAGE image;
    TCHAR imagePath[] = _T("./R.png");
    loadimage(&image, imagePath);
    cout<<imagePath<<endl;
    putimage(18.5*PIXEL_SIZE,4*PIXEL_SIZE, &image);

    // settextcolor(0x800000);
    // outtextxy(27*PIXEL_SIZE,10*PIXEL_SIZE,_T("贪        吃        蛇"));

    //展示菜单
    settextcolor(RED);
    outtextxy(17*PIXEL_SIZE,20*PIXEL_SIZE,_T("1.开始游戏"));
    outtextxy(24*PIXEL_SIZE,20*PIXEL_SIZE,_T("2.游戏说明"));
    outtextxy(31*PIXEL_SIZE,20*PIXEL_SIZE,_T("3.历史成绩"));
    outtextxy(38*PIXEL_SIZE,20*PIXEL_SIZE,_T("4.退出游戏"));
    settextcolor(YELLOW);
    outtextxy(27*PIXEL_SIZE,30*PIXEL_SIZE,_T("请按数字键选择"));
    settextcolor(WHITE);
    outtextxy(40*PIXEL_SIZE,35*PIXEL_SIZE,_T("江紫檀 2022141460178"));

    //监听键盘输入，根据输入跳转到不同的界面
    while(true)
    {
        if(GetAsyncKeyState('1') & 0x8000)
        {
            cleardevice();
            game();
            break;
        }
        if(GetAsyncKeyState('2') & 0x8000)
        {
            cleardevice();
            explain();
            break;
        }
        if(GetAsyncKeyState('3') & 0x8000)
        {
            cleardevice();
            log();
            break;
        }
        if(GetAsyncKeyState('4') & 0x8000)
        {
            closegraph();
            exit(0);
            break;
        }
    }
}

//游戏界面
void map::game()
{
    //画出游戏边界
    setlinecolor(WHITE);
    setlinestyle(PS_SOLID | PS_ENDCAP_FLAT);
    line(1*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE, 1*PIXEL_SIZE);       // 上边界线
    line(1*PIXEL_SIZE, 1*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE);     // 左边界线
    line(1*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE); // 下边界线
    line(41*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE);   // 右边界线

    //展示游戏信息和说明
    outtextxy(45*PIXEL_SIZE,5*PIXEL_SIZE,_T("得分："));
    TCHAR str[10];
    _stprintf_s(str,_T("%d"),score);
    outtextxy(48*PIXEL_SIZE,5*PIXEL_SIZE,str);
    outtextxy(45*PIXEL_SIZE,10*PIXEL_SIZE,_T("每个食物得分：1"));
    outtextxy(45*PIXEL_SIZE,15*PIXEL_SIZE,_T("不能撞墙，不能撞自己！"));
    outtextxy(45*PIXEL_SIZE,20*PIXEL_SIZE,_T("用方向键控制蛇的移动方向！"));
    outtextxy(45*PIXEL_SIZE,25*PIXEL_SIZE,_T("F1键加速，F2键减速！"));
    outtextxy(45*PIXEL_SIZE,30*PIXEL_SIZE,_T("按空格键暂停，按BACK键继续！"));
    outtextxy(45*PIXEL_SIZE,35*PIXEL_SIZE,_T("按ESC键退出！"));

    // 初始化蛇和食物
    snake* head = new snake;
    snake* p = new snake;
    head->setX(21);
    head->setY(20);
    p->setNext(NULL);
    head->setNext(p);
    food food;
    do
    {
        food.setX(rand() % 40+ 1);
        food.setY(rand() % 40 + 1);
    }while (food.getX() == head->getX() && food.getY() == head->getY()||(food.getX()>40||food.getX()<=0)||(food.getY()>40||food.getY()<=0));
    food.draw();
    head->move(direction,&food);

    //监听键盘输入，根据输入执行不同的操作
    while(true)
    {
        if(GetAsyncKeyState(VK_SPACE)&0x8000)  //暂停
        {
            while(true)
            {
                if(GetAsyncKeyState(VK_BACK)&0x8000)
                {
                    break;
                }
            }
        }
        if(GetAsyncKeyState(VK_F1)&0x8000)      //加速
        {
            head->speedUp();
        }
        if(GetAsyncKeyState(VK_F2)&0x8000)      //减速
        {
            head->speedDown();
        }
        if(head->isEatSelf()||head->isHitWall())        //判断是否结束游戏
        {
            while(head->getNext()!=NULL)
            {
                snake* p = head->getNext();
                head->setNext(p->getNext());
                delete p;
            }
            cleardevice();
            endgame();
        }

        head->move(direction,&food);    //移动蛇

        //刷新得分
        delCell(48,5);
        TCHAR str[10];
        _stprintf_s(str,_T("%d"),score);
        outtextxy(48*PIXEL_SIZE,5*PIXEL_SIZE,str);

        //恢复可能被删除的边界线
        line(1*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE, 1*PIXEL_SIZE);       // 上边界线
        line(1*PIXEL_SIZE, 1*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE);     // 左边界线
        line(1*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE); // 下边界线
        line(41*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE);   // 右边界线

        //延时以控制蛇的移动速度
        Sleep(speed);
    }


}

//游戏说明界面
void map::explain()
{
    outtextxy(27*PIXEL_SIZE,10*PIXEL_SIZE,_T("游戏说明："));
    outtextxy(27*PIXEL_SIZE,15*PIXEL_SIZE,_T("1.不能撞墙，不能撞自己！"));
    outtextxy(27*PIXEL_SIZE,20*PIXEL_SIZE,_T("2.用方向键控制蛇的移动方向！"));
    outtextxy(27*PIXEL_SIZE,25*PIXEL_SIZE,_T("3.F1键加速，F2键减速！"));
    outtextxy(27*PIXEL_SIZE,30*PIXEL_SIZE,_T("4.按空格键暂停，按ESC键退出！"));
    outtextxy(27*PIXEL_SIZE,35*PIXEL_SIZE,_T("5.按空格键返回！"));
    while (true)
    {
        if(GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            cleardevice();
            start();
            break;
        }
    }
}

//游戏结束界面
void map::endgame()
{
    outtextxy(27*PIXEL_SIZE,10*PIXEL_SIZE,_T("游戏结束！"));
    outtextxy(27*PIXEL_SIZE,20*PIXEL_SIZE,_T("得分："));
    TCHAR str[10];
    _stprintf_s(str,_T("%d"),score);
    outtextxy(30*PIXEL_SIZE,20*PIXEL_SIZE,str);
    outtextxy(27*PIXEL_SIZE,24*PIXEL_SIZE,score);
    outtextxy(27*PIXEL_SIZE,25*PIXEL_SIZE,_T("按ESC键退出！"));
    outtextxy(27*PIXEL_SIZE,30*PIXEL_SIZE,_T("按空格键回到主菜单！"));

    //把得分写入文件
    mdata d("score.txt");
    d.read();
    d<<score;
    d.msort();
    d.write();

    while (true)
    {
        if(GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            score = 0;
            speed = 120;
            direction = RIGHT;
            cleardevice();
            start();
            break;
        }
    }

}

//历史成绩界面
void map::log()
{
    settextstyle(20,0,_T("宋体"));
    outtextxy(27*PIXEL_SIZE,3*PIXEL_SIZE,_T("历史成绩："));

    //读取文件中的数据并排序后显示
    mdata d("score.txt");
    d.read();
    d.msort();
    d.show();

    outtextxy(27*PIXEL_SIZE,38*PIXEL_SIZE,_T("按C键清除所有记录！"));
    outtextxy(27*PIXEL_SIZE,40*PIXEL_SIZE,_T("按空格键返回！"));
    while (true)
    {
        if(GetAsyncKeyState('C') & 0x8000)
        {
            d.clear();
            d.write();
            cleardevice();
            log();
            break;
        }
        if(GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            cleardevice();
            start();
            break;
        }
    }
}