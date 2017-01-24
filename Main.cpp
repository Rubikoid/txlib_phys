#include "Balls.h"
#include "grap.h"

int main() {
    //vars
    long Time = 0, T0 = 0;
    vector<ball> items = vector<ball>(0);
    items.push_back(ball(Vector2(300,100), Vector2(4, 2), 30, RGB(255,0,0),0));
    items.push_back(ball(Vector2(100, 40), Vector2(6, 4), 20, RGB(100,200,0),1));
    items.push_back(ball(Vector2(400,300), Vector2(2, 5), 25, RGB(50,150,100),2));
    items.push_back(ball(Vector2(300,150), Vector2(8, 1), 15, RGB(150,10,200),3));
    //vars
    init(800,500);
    Time = TIME;
    T0 = Time;
    begin();
    while(!KEY(VK_ESCAPE)) {
        resetCol();
        clear();
        for(int i =0;i<items.size();i++) {
            items[i].drow();
            items[i].update();
        }
        for(int i=0; i<items.size();i++) {
            for(int j=0; j<items.size();j++) {
                if(i!=j) items[i].ballCheck(items[j]);
            }
        }
        gsleep(10);
    }
    end();
    return 0;
}
