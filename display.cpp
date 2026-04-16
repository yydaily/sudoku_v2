#include<iostream>
#include "./display.h"

void displayer::my_set(int x, int y, int v, char data[60][60]) {
    for(auto i : big_fill[v]) {
        data[x+i.first][y+i.second] = 1;
    }
}

void displayer::display(class Ceil ceil[10][10]) {
    char data[60][60];
    memset(data, ' ', sizeof(data));
    for(int i = 0;i<53;i++) {
        data[i][53] = '\0';
    }
    for(int i = 0;i<9;i++) {
        for(int j = 0;j<9;j++) {
            if(ceil[i+1][j+1].value_exact>0) {
                my_set(i*5 + i, j*5 + j, ceil[i+1][j+1].value_exact, data);
            }
        }
    }
    for(int i = 0;i<9;i++) {
        for(int j = 0;j<9;j++) {
            for(int k = 1;k<=9;k++) {
                if(ceil[i+1][j+1].value_exact == 0 && (ceil[i+1][j+1].can_choose&(1<<k))) {
                    data[i*6+(k-1)/3*2][j*6+(k-1)%3*2] = k+'0';
                }
            }
        }
    }
    for(int i = 0;i<53;i++) {
        for(int j = 0;j<53;j++) {
            if(i%18 == 17||j%18 == 17) {
                std::cout<<"\033[47m"<<' '<<"\033[0m";
                continue;
            }
            if(data[i][j] == 1) {
                std::cout<<"\033[42m"<<' '<<"\033[0m";
            } else {
                std::cout<<data[i][j];
            }
        }
        std::cout<<std::endl;
    }
}

std::string ToString(int i) {
    return std::to_string(i);
}
