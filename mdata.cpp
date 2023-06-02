//
// Created by jzita on 2023/6/2.
//

#include <easyx.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <tchar.h>
#include "mdata.h"

// 定义像素的大小
#define PIXEL_SIZE 15

using namespace std;
mdata::mdata(string filename)       //初始化文件名
{
this->filename = filename;
}
void mdata::read()     //读取文件，如果不存在则创建文件
{
    ifstream in(filename);
    if(!in)
    {
        ofstream out(filename);
        if(!out)
        {
            cout<<"创建文件失败！"<<endl;
            exit(1);
        }
    }
    int temp;
    while(in>>temp)
    {
        score.push_back(temp);
    }
    in.close();
}
void mdata::write()        //写入文件
{
    ofstream out(filename);
    if(!out)
    {
        cout<<"打开文件失败！"<<endl;
        exit(1);
    }
    for(int i=0;i<score.size();i++)
    {
        out<<score[i]<<endl;
    }
    out.close();
}
istream& mdata::operator<<(int s)     //添加数据
{
    score.push_back(s);
}
void mdata::msort()        //排序
{
    sort(score.begin(),score.end(),greater<int>());
}
void mdata::show()     //显示数据
{

    for(int i=10;i<score.size()*2+10;i+=2)
    {
        outtextxy(15*PIXEL_SIZE,i*PIXEL_SIZE,_T("第"));
        TCHAR str[10];
        _stprintf_s(str,_T("%d"),(i-8)/2);
        outtextxy(17*PIXEL_SIZE,i*PIXEL_SIZE,str);
        outtextxy(19*PIXEL_SIZE,i*PIXEL_SIZE,_T("名："));
        _stprintf_s(str,_T("%d"),score[(i-8)/2-1]);
        outtextxy(21*PIXEL_SIZE,i*PIXEL_SIZE,str);
    }
}
void mdata::clear()        //清除数据
{
    score.clear();
}