#ifndef TOOLS_H
#define TOOLS_H

#include<set>

std::set<std::pair<int, int>> affect_ceils(int a, int b);
std::set<std::pair<int, int>> affect_ceils(const std::pair<int, int> &poi);
template<typename T>
std::set<T> join_set(const std::set<T>&a, const std::set<T> &b) {
    std::set<T> result;

    // 计算交集：元素必须同时存在于 a 和 b 中
    std::set_intersection(a.begin(), a.end(),
                          b.begin(), b.end(),
                          std::inserter(result, result.begin()));
    return result;
}
int box_index(int a, int b); // 返回宫号, 1~9
int index_in_box(int a, int b); // 返回在宫内的编号, 1~9
std::vector<int> mask2vec(int mask); // mask转下标
std::pair<int, int> box_index2pos(int box_index, int index); // 宫内编号变成坐标
bool mask_contain(int mask, int v); // 判断v是不是在mask里面

#endif
