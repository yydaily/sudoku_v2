#ifndef BASE_H
#define BASE_H

#include "tools.h"

#include<iostream>
const int mask = (1<<10)-2;

class Ceil {
public:
    int value_exact;
    int can_choose;

    Ceil() {};
    Ceil(int _v, int _c = mask) : value_exact(_v), can_choose(_c) {};
};

class Map {
public:
    Ceil mat[10][10];
    int row_mask[10][10], column_mask[10][10], box_mask[10][10];
    // 值为v，第i行/列/宫有哪些位置

    Map() {
        for(int i = 1;i<=9;i++) {
            for(int j = 1;j<=9;j++) {
                mat[i][j] = Ceil();
                row_mask[i][j] = mask;
                column_mask[i][j] = mask;
                box_mask[i][j] = mask;
            }
        }
    }

    // 清除 (x,y) 的 v候选
    void clear_choose(int x, int y, int v);

    // 如果 x,y 确定是v，清除 (x,y) 范围内所有可候选的v
    void set_value(int x, int y, int v);

    // 输入
    void input();

    // 是否解出来了
    bool solved();
};

#endif
