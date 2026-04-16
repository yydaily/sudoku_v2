#include "tools.h"

std::set<std::pair<int, int>> affect_ceils(int a, int b) {
    std::set<std::pair<int, int>> ret;
    int blocks = box_index(a, b); // 1~9
    for(int i = 1;i<=9;i++) {
        ret.insert({a, i});
        ret.insert({i, b});
        ret.insert({(blocks-1)/3*3+(i-1)/3+1, (blocks-1)%3*3+(i-1)%3+1});
    }
    ret.erase({a, b});
    return ret;
}

std::set<std::pair<int, int>> affect_ceils(const std::pair<int, int> &poi) {
    return affect_ceils(poi.first, poi.second);
}

int box_index(int a, int b) {
    return (a-1)/3*3 + (b-1)/3+1;
}

int index_in_box(int a, int b) {
    return (a-1)%3*3 + (b-1)%3 + 1;
}

std::pair<int, int> box_index2pos(int box_index, int index) {
    int x = (box_index-1)/3*3 + (index-1)/3 + 1;
    int y = (box_index-1)%3*3 + (index-1)%3 + 1;
    return {x, y};
}

std::vector<int> mask2vec(int mask) {
    std::vector<int> ret;
    for(int i = 1;i<=9;i++) if(mask&(1<<i)) ret.push_back(i);
    return ret;
}

bool mask_contain(int mask, int v) {
    return (mask&v) == v;
}
