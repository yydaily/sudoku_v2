#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <string>
#include <set>
#include "base.h"

class displayer {
private:
    std::vector<std::pair<int, int>> big_fill[10];
    void my_set(int x, int y, int v, char data[60][60]);

public:
    displayer() {
        big_fill[1] = {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}};
        big_fill[2] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {3, 0}, {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}};
        big_fill[3] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}};
        big_fill[4] = {{0, 0}, {0, 4}, {1, 0}, {1, 4}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {3, 4}, {4, 4}};
        big_fill[5] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 0}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}};
        big_fill[6] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 0}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {3, 0}, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}};
        big_fill[7] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}};
        big_fill[8] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 0}, {1, 4}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {3, 0}, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}};
        big_fill[9] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 0}, {1, 4}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}};
    }

    void display(class Ceil ceil[10][10]);
};

// 基础重载声明（在 display.cpp 中定义）
std::string ToString(int i);

// 模板重载需放在头文件中，避免链接错误
template<typename T1, typename T2>
std::string ToString(const std::pair<T1, T2> & t) {
    return "(" + ToString(t.first) + "," + ToString(t.second) + ")";
}

template<typename T>
std::string ToString(const std::vector<T> &v) {
    std::string res = "[";
    for (size_t i = 0; i < v.size(); i++) {
        res += ToString(v[i]);
        if (i + 1 != v.size()) res += ",";
    }
    res += "]";
    return res;
}

template<typename T>
std::string ToString(const std::set<T> &v) {
    std::string res = "{";
    for (auto i : v) {
        res += ToString(i);
        res += ",";
    }
    res += "}";
    return res;
}

#endif
