#include "plan.h"

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
            if((m.row_mask[v][i] & 14) == m.row_mask[v][i]) {
                // 第i行，只有第1宫有v，删除1宫里面其他的v
                auto box_ind = box_index(i, 1);
            }
        }
    }
}
