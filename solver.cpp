#include<iostream>
#include "display.h"
#include "base.h"
#include "plan.h"
using namespace std;
displayer d;
int main() {
    Map m;
    m.input();

    vector<Plan*> ps = {
        new Plan1(),
        new Plan2(),
        new Plan3(),
        new Plan4(),
        new Plan5(),
        new Plan6(),
        new Plan7(),
        new Plan8(),
        new Plan9(),
    };

    int cnt = 0;
    while(!m.solved() && (cnt++) < 90) {
        // d.display(m.mat);
        bool update = false;
        for(auto p : ps) {
            update |= p->handle(m);
            if(update) break;
        }
        if(!update) break;
    }

    d.display(m.mat);
    return 0;
}
