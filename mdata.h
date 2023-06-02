//
// Created by jzita on 2023/6/2.
//

#ifndef SNAKE_GAME_MDATA_H
#define SNAKE_GAME_MDATA_H
#include <vector>
#include <string>

using namespace std;

class mdata
{
private:
    string filename;        //文件名
    vector<int> score;      //存储数据
public:
    mdata(string filename);       //初始化文件名
    void read();     //读取文件，如果不存在则创建文件
    void write();        //写入文件
    istream& operator<<(int s);     //添加数据
    void msort();        //排序
    void show();     //显示数据
    void clear();        //清除数据
};


#endif //SNAKE_GAME_MDATA_H
