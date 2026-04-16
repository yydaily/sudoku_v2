#ifndef TOOLS_H
#define TOOLS_H

#include<set>

std::set<std::pair<int, int>> affect_ceils(int a, int b);
int box_index(int a, int b); // 返回宫号, 1~9
int index_in_box(int a, int b); // 返回在宫内的编号, 1~9
std::vector<int> mask2vec(int mask); // mask转下标
std::pair<int, int> box_index2pos(int box_index, int index); // 宫内编号变成坐标

#endif
