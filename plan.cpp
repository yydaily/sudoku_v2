#include <set>
#include <cassert>
#include "base.h"
#include "plan.h"
#include "tools.h"
#include "display.h"

bool Plan1::handle(Map &m) {
    for(int v = 1;v<=9;v++) {
        for(int i = 1;i<=9;i++) {
            if(__builtin_popcount(m.row_mask[v][i]) == 1) {
                auto index = mask2vec(m.row_mask[v][i])[0];
                m.set_value(i, index, v);
                std::cout<<"[规则1.1] 第"<<i<<"行只有1个位置可以填"<<v
                    <<"\t("<<i<<","<<index<<") -> "<<v<<std::endl;
                return true;
            }
            if(__builtin_popcount(m.column_mask[v][i]) == 1) {
                auto index = mask2vec(m.column_mask[v][i])[0];
                m.set_value(index, i, v);
                std::cout<<"[规则1.2] 第"<<i<<"列只有1个位置可以填"<<v
                    <<"\t("<<index<<","<<i<<") -> "<<v<<std::endl;
                return true;
            }
            if(__builtin_popcount(m.box_mask[v][i]) == 1) {
                auto box_index = mask2vec(m.box_mask[v][i])[0];
                auto pos = box_index2pos(i, box_index);
                m.set_value(pos.first, pos.second, v);
                std::cout<<"[规则1.3] 第"<<i<<"宫只有1个位置可以填"<<v
                    <<"\t("<<pos.first<<","<<pos.second<<") -> "<<v<<std::endl;
                return true;
            }
            if(__builtin_popcount(m.mat[v][i].can_choose) == 1) {
                auto index = mask2vec(m.mat[v][i].can_choose)[0];
                m.set_value(v, i, index);
                std::cout<<"[规则1.4] 第"<<v<<"行第"<<i<<"列只有1个数字可以填"<<index
                    <<"\t("<<v<<","<<i<<") -> "<<index<<std::endl;
            }
        }
    }
    return false;
}

bool Plan2::handle(Map &m) {
    for(int i = 1;i<=9;i++) {
        for(int j = 1;j<=9;j++) {
            if(__builtin_popcount(m.mat[i][j].can_choose) == 1) {
                auto index = mask2vec(m.mat[i][j].can_choose)[0];
                m.set_value(i, j, index);
                std::cout<<"[规则2] 第"<<i<<"行第"<<j<<"列只有1个数字可以填"<<index
                    <<"\t("<<i<<","<<j<<") -> "<<index<<std::endl;
                return true;
            }
        }
    }
    return false;
}

bool Plan3::handle(Map &m) {
    for(int v = 1;v<=9;v++) {
        for(int i = 1;i<=9;i++) {
            std::vector<std::pair<int, int>> erases;
            for(int j = 1;j<=3;j++) {
                auto mm = (m.row_mask[v][i] & (14<<(j*3-3)));
                if(mm > 0 && mm == m.row_mask[v][i]) {
                    // 第i行，只有第j宫有v，删除j宫其他的v
                    auto box_ind = box_index(i, j*3); // 区块所在的宫号
                    // 删除box_ind这一宫其他的v
                    for(auto idx : mask2vec(m.box_mask[v][box_ind])) {
                        auto pos = box_index2pos(box_ind, idx);
                        if(pos.first == i) continue;
                        erases.push_back(pos);
                    }
                    
                    if(erases.size() > 0) {
                        std::cout<<"[规则3.1] 第"<<i<<"行有值为"<<v<<"的区块，删除"<<ToString(erases).c_str()<<"中的"<<v<<std::endl;
                        for(auto e : erases) {
                            m.clear_choose(e.first, e.second, v);
                        }
                        return true;
                    }
                }

                mm = (m.column_mask[v][i] & (14<<(j*3-3)));
                if(mm > 0 && mm == m.column_mask[v][i]) {
                    // 第i列，只有第j宫有v，删除i列其他的v
                    auto box_ind = box_index(j*3, i); // 区块所在的宫号
                    // 删除box_ind这一宫其他的v
                    for(auto idx : mask2vec(m.box_mask[v][box_ind])) {
                        auto pos = box_index2pos(box_ind, idx);
                        if(pos.second == i) continue;
                        erases.push_back(pos);
                    }
                    
                    if(erases.size() > 0) {
                        std::cout<<"[规则3.2] 第"<<i<<"列有值为"<<v<<"的区块，删除"<<ToString(erases).c_str()<<"中的"<<v<<std::endl;
                        for(auto e : erases) {
                            m.clear_choose(e.first, e.second, v);
                        }
                        return true;
                    }
                }

                mm = (m.box_mask[v][i] & (14<<(j*3-3)));
                if(mm > 0 && mm == m.box_mask[v][i]) {
                    // 第i宫，只有第j行有v，删除i宫其他的v
                    int row_index = (i-1)/3*3+j;
                    for(auto idx : mask2vec(m.row_mask[v][row_index])) {
                        if(m.mat[row_index][idx].box_index == i) continue;
                        erases.push_back({row_index, idx});
                    }
                    
                    if(erases.size() > 0) {
                        std::cout<<"[规则3.3] 第"<<i<<"宫有值为"<<v<<"的区块，删除"<<ToString(erases).c_str()<<"中的"<<v<<std::endl;
                        for(auto e : erases) {
                            m.clear_choose(e.first, e.second, v);
                        }
                        return true;
                    }
                }

                mm = (m.box_mask[v][i] & (146<<(j-1)));
                if(mm > 0 && mm == m.box_mask[v][i]) {
                    int column_index = (i-1)%3*3+j;
                    for(auto idx : mask2vec(m.column_mask[v][column_index])) {
                        if(m.mat[idx][column_index].box_index == i) continue;
                        erases.push_back({idx, column_index});
                    }
                    
                    if(erases.size() > 0) {
                        std::cout<<"[规则3.4] 第"<<i<<"宫有值为"<<v<<"的区块，删除"<<ToString(erases).c_str()<<"中的"<<v<<std::endl;
                        for(auto e : erases) {
                            m.clear_choose(e.first, e.second, v);
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// 9*9*9*512
bool Plan4::handle(Map &m) {
    for(int mask = 2;mask<1024;mask+=2) {
        for(int i = 1;i<=9;i++) {
            std::set<int> indexes;
            bool filter = false;
            for(auto v : mask2vec(mask)) {
                if(__builtin_popcount(m.row_mask[v][i]) == 0) {filter = true; break;}
                for(auto ind : mask2vec(m.row_mask[v][i])) indexes.insert(ind);
                if(indexes.size() > __builtin_popcount(mask)) {filter = true; break;}
            }
            if(filter) continue;

            assert(indexes.size() <= __builtin_popcount(mask));

            std::vector<std::tuple<int, int, int>> erases;

            for(int j = 1;j<=9;j++) {
                if(indexes.count(j)) {
                    if(m.mat[i][j].can_choose ^ (m.mat[i][j].can_choose & mask)) {
                        for(auto e : mask2vec(m.mat[i][j].can_choose ^ (m.mat[i][j].can_choose & mask))) {
                            erases.push_back({i, j, e});
                        }
                    }
                    continue;
                }
                if((m.mat[i][j].can_choose & mask) == 0) continue;
                for(auto v : mask2vec(m.mat[i][j].can_choose & mask)) {
                    erases.push_back({i, j, v});
                }
            }
            if(erases.size() > 0) {
                std::cout<<"[规则4] 第"<<i<<"行有值为"<<ToString(mask2vec(mask))<<"的候选数，删除"<<ToString(erases)<<std::endl;
                for(auto &e : erases) {
                    m.clear_choose(std::get<0>(e), std::get<1>(e), std::get<2>(e));
                }
                return true;
            }
        }

        for(int c = 1;c<=9;c++) {
            std::set<int> indexes;
            bool filter = false;
            for(auto v : mask2vec(mask)) {
                if(__builtin_popcount(m.column_mask[v][c]) == 0) {filter = true; break;}
                for(auto ind : mask2vec(m.column_mask[v][c])) indexes.insert(ind);
                if(indexes.size() > __builtin_popcount(mask)) {filter = true; break;}
            }
            if(filter) continue;

            assert(indexes.size() <= __builtin_popcount(mask));

            std::vector<std::tuple<int, int, int>> erases;

            for(int r = 1;r<=9;r++) {
                if(indexes.count(r)) {
                    if(m.mat[r][c].can_choose ^ (m.mat[r][c].can_choose & mask)) {
                        for(auto e : mask2vec(m.mat[r][c].can_choose ^ (m.mat[r][c].can_choose & mask))) {
                            erases.push_back({r, c, e});
                        }
                    }
                    continue;
                }
                if((m.mat[r][c].can_choose & mask) == 0) continue;
                for(auto v : mask2vec(m.mat[r][c].can_choose & mask)) {
                    erases.push_back({r, c, v});
                }
            }

            if(erases.size() > 0) {
                std::cout<<"[规则4] 第"<<c<<"列有值为"<<ToString(mask2vec(mask))<<"的候选数，删除"<<ToString(erases)<<std::endl;
                for(auto &e : erases) {
                    m.clear_choose(std::get<0>(e), std::get<1>(e), std::get<2>(e));
                }
                return true;
            }
        }
    }
    return false;
}

bool Plan5::handle(Map &m) {
    for(int v = 1;v<=9;v++) {
        for(int i = 1;i<=9;i++) { // 行号
            if(__builtin_popcount(m.row_mask[v][i]) != 2) continue;
            if(mask_contain(14, m.row_mask[v][i]) ||  // 如果在同一宫，直接忽略
               mask_contain(112, m.row_mask[v][i]) || 
               mask_contain(896, m.row_mask[v][i])) continue;

            std::vector<int> ms = mask2vec(m.row_mask[v][i]);
            int masks = (14<<((ms[0]-1)/3*3)) + (14<<((ms[1]-1)/3*3));

            for(int j = 1;j<=9;j++) {
                if((j-1)/3 == (i-1)/3 || (m.row_mask[v][j] & masks) != m.row_mask[v][j]) continue; // 必须在这两宫里面

                std::vector<std::pair<int, int>> erases;
                if((m.row_mask[v][j] & (14<<((ms[0]-1)/3*3)))  == (1<<ms[0])) { // ms[0]这一列只有一个
                    auto box_ind = box_index(j, ms[1]);
                    for(int ind = 1;ind<=9;ind++) {
                        auto pos = box_index2pos(box_ind, ind);
                        if(pos.first == j || pos.second != ms[1]) continue;
                        if(m.mat[pos.first][pos.second].can_choose & (1<<v)) {
                            erases.push_back({pos.first, pos.second});
                        }
                    }
                }
                if((m.row_mask[v][j] & (14<<((ms[1]-1)/3*3)))  == (1<<ms[1])) { // ms[1]这一列只有一个
                    auto box_ind = box_index(j, ms[0]);
                    for(int ind = 1;ind<=9;ind++) {
                        auto pos = box_index2pos(box_ind, ind);
                        if(pos.first == j || pos.second != ms[0]) continue;
                        if(m.mat[pos.first][pos.second].can_choose & (1<<v)) {
                            erases.push_back({pos.first, pos.second});
                        }
                    }
                }

                if(erases.size() > 0) {
                    std::cout<<"[规则5] 值为"<<v<<" 行号为"<<i<<","<<j<<"的两行构成了鱼，删除"<<ToString(erases)<<"中的"<<v<<std::endl;
                    for(auto &e : erases) {
                        m.clear_choose(e.first, e.second, v);
                    }
                    return true;
                }
            }
        }

        for(int i = 1;i<=9;i++) { // 列号
            if(__builtin_popcount(m.column_mask[v][i]) != 2) continue;
            if(mask_contain(14, m.column_mask[v][i]) ||  // 如果在同一宫，直接忽略
               mask_contain(112, m.column_mask[v][i]) || 
               mask_contain(896, m.column_mask[v][i])) continue;

            std::vector<int> ms = mask2vec(m.column_mask[v][i]);
            int masks = (14<<((ms[0]-1)/3*3)) + (14<<((ms[1]-1)/3*3));

            for(int j = 1;j<=9;j++) {
                bool log = (v==6&&i==2&&j==5);
                if((j-1)/3 == (i-1)/3 || (m.column_mask[v][j] & masks) != m.column_mask[v][j]) continue; // 必须在这两宫里面

                std::vector<std::pair<int, int>> erases;
                if((m.column_mask[v][j] & (14<<((ms[0]-1)/3*3)))  == (1<<ms[0])) { // ms[0]这一行只有一个
                    auto box_ind = box_index(ms[1], j);
                    for(int ind = 1;ind<=9;ind++) {
                        auto pos = box_index2pos(box_ind, ind);
                        if(pos.first != ms[1] || pos.second == j) continue;
                        if(m.mat[pos.first][pos.second].can_choose & (1<<v)) {
                            erases.push_back({pos.first, pos.second});
                        }
                    }
                }
                if((m.column_mask[v][j] & (14<<((ms[1]-1)/3*3)))  == (1<<ms[1])) { // ms[1]这一行只有一个
                    auto box_ind = box_index(ms[0], j);
                    for(int ind = 1;ind<=9;ind++) {
                        auto pos = box_index2pos(box_ind, ind);
                        if(pos.first != ms[0] || pos.second == j) continue;
                        if(m.mat[pos.first][pos.second].can_choose & (1<<v)) {
                            erases.push_back({pos.first, pos.second});
                        }
                    }
                }

                if(erases.size() > 0) {
                    std::cout<<"[规则5] 值为"<<v<<" 列号为"<<i<<","<<j<<"的两列构成了鱼，删除"<<ToString(erases)<<"中的"<<v<<std::endl;
                    for(auto &e : erases) {
                        m.clear_choose(e.first, e.second, v);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

// 9*9*9*9
bool Plan6::handle(Map &m) {
    for(int v = 1;v<=9;v++) {
        std::vector<int> row_chooses, column_chooses;
        for(int i = 1;i<=9;i++) {
            if(__builtin_popcount(m.row_mask[v][i]) == 2) row_chooses.push_back(i);
            if(__builtin_popcount(m.column_mask[v][i]) == 2) column_chooses.push_back(i);
        }

        if(row_chooses.size() >= 2) {
            for(auto a : row_chooses) for(auto b : row_chooses) {
                if(a==b) continue;
                if(m.row_mask[v][a] == m.row_mask[v][b]) {
                    auto ind = mask2vec(m.row_mask[v][a]);
                    std::vector<std::pair<int, int>> erases;
                    for(int i = 1;i<=9;i++) {
                        if(i==a || i==b) continue;
                        if(m.mat[i][ind[0]].can_choose & (1<<v)) {
                            erases.push_back({i, ind[0]});
                        }
                        if(m.mat[i][ind[1]].can_choose & (1<<v)) {
                            erases.push_back({i, ind[1]});
                        }
                    }
                    if(erases.size() > 0) {
                        std::cout<<"[规则6] 值为"<<v<<" 行号为"<<a<<","<<b<<"的两行构成了x-wing，删除"<<ToString(erases)<<"中的"<<v<<std::endl;
                        for(auto &e : erases) {
                            m.clear_choose(e.first, e.second, v);
                        }
                        return true;
                    }
                }
            }
        }

        if(column_chooses.size() >= 2) {
            for(auto a : column_chooses) for(auto b : column_chooses) {
                if(a==b) continue;
                if(m.column_mask[v][a] == m.column_mask[v][b]) {
                    auto ind = mask2vec(m.column_mask[v][a]);
                    std::vector<std::pair<int, int>> erases;
                    for(int i = 1;i<=9;i++) {
                        if(i==a || i==b) continue;
                        if(m.mat[ind[0]][i].can_choose & (1<<v)) {
                            erases.push_back({ind[0], i});
                        }
                        if(m.mat[ind[1]][i].can_choose & (1<<v)) {
                            erases.push_back({ind[1], i});
                        }
                    }
                    if(erases.size() > 0) {
                        std::cout<<"[规则6] 值为"<<v<<" 列号为"<<a<<","<<b<<"的两列构成了x-wing，删除"<<ToString(erases)<<"中的"<<v<<std::endl;
                        for(auto &e : erases) {
                            m.clear_choose(e.first, e.second, v);
                        }
                    }
                }
            }
        }
    }
    return false;
}

// xy-wing
bool Plan7::handle(Map &m) {
    std::vector<std::pair<int, int>> chooses[10][10];
    for(int i = 1;i<=9;i++) {
        for(int j = 1;j<=9;j++) {
            if(__builtin_popcount(m.mat[i][j].can_choose) == 2) {
                auto x = mask2vec(m.mat[i][j].can_choose);
                chooses[x[0]][x[1]].push_back({i, j});
                chooses[x[1]][x[0]].push_back({i, j});
            }
        }
    }

    std::function<bool(std::pair<int, int>, std::pair<int, int>)> copair = [&](std::pair<int, int> a, std::pair<int, int> b) {
        if(a.first == b.first) return true;
        if(a.second == b.second) return true;
        if(box_index(a.first, a.second) == box_index(b.first, b.second)) return true;
        return false;
    };

    std::function<bool(std::vector<std::pair<int, int>>[10][10], int, int, int)> f = [&](std::vector<std::pair<int, int>> v[10][10], int x, int y, int z) -> bool {
        for(auto ind : v[x][y]) {
            for(auto ind2 : v[y][z]) {
                if(!copair(ind, ind2)) continue;
                for(auto ind3 : v[x][z]) {
                    if(!copair(ind, ind3)) continue;

                    auto c = affect_ceils(ind2.first, ind2.second);
                    auto c2 = affect_ceils(ind3.first, ind3.second);

                    std::vector<std::pair<int, int>> ret;
                    auto cc = join_set(c, c2);
                    for(auto ind4 : cc) {
                        if(m.mat[ind4.first][ind4.second].can_choose & (1<<z)) {
                            ret.push_back(ind4);
                        }
                    }
                    if(ret.size() > 0) {
                        std::cout<<"[规则7] "<<ToString(ind)<<","<<ToString(ind2)<<"和"<<ToString(ind3)<<"构成了xy-wing，删除"<<ToString(ret)<<"中的"<<z<<std::endl;
                        for(auto &e : ret) {
                            m.clear_choose(e.first, e.second, z);
                        }
                        return true;
                    }
                }
            }
        }
        return false;
    };

    for(int x = 1;x<=9;x++) {
        for(int y = x+1;y<=9;y++) {
            if(chooses[x][y].size() == 0) continue;
            for(int z = 1;z<=9;z++) {
                if(chooses[x][z].size() == 0 || chooses[y][z].size() == 0) continue;
                if(f(chooses, x, y, z)) return true;
            }
        }
    }
    return false;
}

// xyz-wing
bool Plan8::handle(Map &m) {
    std::vector<std::pair<int, int>> index3;
    for(int i = 1;i<=9;i++) {
        for(int j = 1;j<=9;j++) {
            int cnt = __builtin_popcount(m.mat[i][j].can_choose);
            if(cnt==3) index3.push_back({i, j});
        }
    }

    for(auto const &ind3 : index3) {
        std::vector<std::pair<int, int>> candidates;
        for(auto poi : affect_ceils(ind3)) {
            if(__builtin_popcount(m[poi].can_choose) == 2 && mask_contain(m[ind3].can_choose, m[poi].can_choose)) {
                candidates.push_back(poi);
            }
        }

        for(int i = 0;i<candidates.size();i++) {
            for(int j = i+1;j<candidates.size();j++) {
                if(m[candidates[i]].can_choose == m[candidates[j]].can_choose) continue;

                auto aff = join_set(affect_ceils(candidates[i]), join_set(affect_ceils(candidates[j]), affect_ceils(ind3)));

                auto mm = m[ind3].can_choose & m[candidates[i]].can_choose & m[candidates[j]].can_choose;
                std::vector<std::pair<int, int>> erases;
                for(auto poi : aff) {
                    if(m[poi].can_choose & mm) {
                        erases.push_back(poi);
                    }
                }

                if(erases.size()) {
                    int v = mask2vec(mm)[0];
                    std::cout<<"[规则8] "<<ToString(ind3)<<"和"<<ToString(candidates[i])<<"和"<<ToString(candidates[j])<<"构成了xyz-wing，删除"<<ToString(erases)<<"中的"<<v<<std::endl;
                    for(auto poi : erases) {
                        m.clear_choose(poi, v);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

// 双强链
bool Plan9::handle(Map &m) {
    for(int v = 1;v<=9;v++) {
        // 找到所有v的强链
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> links;
        for(int i = 1;i<=9;i++) {
            auto indexes = mask2vec(m.row_mask[v][i]);
            if(indexes.size()==2) {
                links.push_back({{i, indexes[0]}, {i, indexes[1]}});
                links.push_back({{i, indexes[1]}, {i, indexes[0]}});
            }

            indexes = mask2vec(m.column_mask[v][i]);
            if(indexes.size()==2) {
                links.push_back({{indexes[0], i}, {indexes[1], i}});
                links.push_back({{indexes[1], i}, {indexes[0], i}});
            }

            indexes = mask2vec(m.box_mask[v][i]);
            if(indexes.size()==2) {
                links.push_back({box_index2pos(i, indexes[0]), box_index2pos(i, indexes[1])});
                links.push_back({box_index2pos(i, indexes[1]), box_index2pos(i, indexes[0])});
            }
        }

        for(int i = 0;i<links.size();i++) {
            for(int j = i+1;j<links.size();j++) {
                if(links[i].second == links[j].first) continue;
                auto x = affect_ceils(links[i].second);
                if(x.find(links[j].first) == x.end()) continue;

                auto pois = join_set(affect_ceils(links[i].first), affect_ceils(links[j].second));
                pois.erase(links[i].first);
                pois.erase(links[j].second);

                std::set<std::pair<int, int>> erases;
                for(auto poi : pois) {
                    if(m[poi].can_choose & (1<<v)) erases.insert(poi);
                }

                if(erases.size()>0) {
                    std::cout<<"[规则9] "<<ToString(links[i])<<"和"<<ToString(links[j])<<"构成了双强链，删除"<<ToString(erases)<<"中的"<<v<<std::endl;
                    for(auto const &poi : erases) {
                        m.clear_choose(poi, v);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}
