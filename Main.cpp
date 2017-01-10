#include "Balls.h"
#include "grap.h"

int main() {
    //vars
    long Time = 0, T0 = 0;
    vector<ball> items = vector<ball>(0);
    items.push_back(ball(300,100,4 ,2, 30, RGB(255,0,0)));
    items.push_back(ball(100,40 ,6,4, 20, RGB(100,200,0)));
    items.push_back(ball(400,300,2, 5, 25, RGB(50,150,100)));
    items.push_back(ball(300,150,8, 1, 15, RGB(150,10,200)));
    //vars
    init(800,500);
    Time = TIME;
    T0 = Time;
    begin();
    while(!KEY(VK_ESCAPE)) {
        resetCol();
        clear();
        for(int i=0;i<items.size();i++) {
            items[i].drow();
            items[i].update();
        }
        gsleep(10);
    }
    end();
    return 0;
}
