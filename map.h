//
// Created by jzita on 2023/5/26.
//
#ifndef SNAKE_GAME_MAP_H
#define SNAKE_GAME_MAP_H

class map
{
private:
    int width;
    int height;
public:
    map(int w, int h);      //初始化地图大小
    void start();     //程序开始界面
    //游戏界面
    void game();
    //游戏说明界面
    void explain();
    //游戏结束界面
    void endgame();
    //历史成绩界面
    void log();
};


#endif //SNAKE_GAME_MAP_H
