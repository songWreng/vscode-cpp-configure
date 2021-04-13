/**************************************************************
@filename: main.cpp
@author: Haisong Weng
@version: 1.0
@date: 2021年4月13日
@description: 
    C/C++ 插件配置
@others: 
    1. 如果安装了 code runner 插件, 可以点击右上角的小三角
       setting.json 具体的配置为(安装会默认配置, 建议修改为在终端运行，才能接收输入，避免输出中文乱码)
@functionlist: 
    1. main 

**************************************************************/

#include<bits/stdc++.h>

using namespace std;

int main()
{
    int i, sum;
    for(i =0, sum=0; i < 5; ++i)
        sum += i;
    cout << "Hello world!" << endl;
    cout << "Hello Haisong Weng" << endl;
    cout << "Hello Haisong Weng" << endl;
    return 0;
}

