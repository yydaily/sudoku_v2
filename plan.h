#ifndef PLAN_H
#define PLAN_H

#include "base.h"

class Plan {
public:
    virtual bool handle(Map &m) = 0;
};

// 如果某一行 / 某一列 / 某一宫只有一个位置可以填某个值，直接填写
// 复杂度 O(9*9)
class Plan1 : public Plan {
    bool handle(Map &m);
};

// 如果某一格里面只有一个候选数，直接填
// 复杂度 O(9*9)
class Plan2 : public Plan {
    bool handle(Map &m);
};

// 区块消除
// 复杂度 O(?)
class Plan3 : public Plan {
    bool handle(Map &m);
};

#endif
