#include "base.h"

void Map::clear_choose(int x, int y, int v) {
    mat[x][y].can_choose &= ~(1<<v); 
    row_mask[v][x] &= ~(1<<y);
    column_mask[v][y] &= ~(1<<x);
    int box_ind = box_index(x, y);
    box_mask[v][box_ind] &= ~(1<<index_in_box(x, y));
}

void Map::clear_choose(const std::pair<int, int> &poi, int v) {
    clear_choose(poi.first, poi.second, v);
}

void Map::set_value(int x, int y, int v) {
    mat[x][y].value_exact = v;
    for(auto p : affect_ceils(x, y)) {
        clear_choose(p, v);
    }
    for(int i = 1;i<=9;i++) clear_choose(x, y, i);
}

void Map::input() {
    std::string buf;
    for(int i = 1;i<=9;i++) {
        std::cin>>buf;
        for(int j = 1;j<=9;j++) {
            mat[i][j] = Ceil(buf[j-1]-'0');
        }
    }
    for(int i = 1;i<=9;i++) {
        for(int j = 1;j<=9;j++) {
            if(mat[i][j].value_exact != 0) {
                set_value(i, j, mat[i][j].value_exact);
            }
        }
    }
}

bool Map::solved() {
    for(int i = 1;i<=9;i++) {
        for(int j = 1;j<=9;j++) {
            if(mat[i][j].value_exact == 0) return false;
        }
    }
    return true;
}
