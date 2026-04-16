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
// 复杂度 O(9^3*3)
class Plan3 : public Plan {
    bool handle(Map &m);
};

// 显性数对
// TODO: 只实现了行的数对
class Plan4 : public Plan {
    bool handle(Map &m);
};

// 鱼
// 复杂度 O(9^4)
class Plan5 : public Plan {
    bool handle(Map &m);
};

// x-wing
// 复杂度 O(9^4)
class Plan6 : public Plan {
    bool handle(Map &m);
};

// xy-wing
class Plan7 : public Plan {
    bool handle(Map &m);
};

// xyz-wing
class Plan8 : public Plan {
    bool handle(Map &m);
};

// 双强链
class Plan9 : public Plan {
    bool handle(Map &m);
};
#endif
