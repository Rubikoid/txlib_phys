#include "Balls.h"
#include "grap.h"

#define WIDTH 1300
#define HEIGHT 700

int iRand(int min, int max) {
    return min + rand() % (max-min+1);
}

int main() {
    //vars
    long Time = 0, T0 = 0;
    vector<ball> items = vector<ball>(0);
    init(WIDTH, HEIGHT);
    Bounds box = Bounds(40,HEIGHT-40,WIDTH-40,40);
    for(int i=0;i<100;i++) {
        int radi = 5;
        int startX = iRand(((int)box.ldPos.x)+radi*2,((int)box.rpPos.x)-radi*2), startY = iRand(((int)box.rpPos.y)+radi*2,((int)box.ldPos.y)-radi*2);
        int speedX = iRand(-10,10), speedY = iRand(-10,10);
        ball next = ball(Vector2((float)startX,(float)startY),     //start pos
                         Vector2((float)speedX,(float)speedY),     //start speed
                         radi,          //mass/radi
                         RGB(iRand(40,240),iRand(40,240),iRand(40,240)),  //color
                         (double)i,             //num
                         box            //box
                         );
        //printf("%d;%d;%f;%f;max=%d\n",startX,startY,next.pos.x,next.pos.y,((int)box.ldPos.y)-radi*2);
        items.push_back(next);
    }
    ball next = ball(Vector2(400,200),     //start pos
                     Vector2(0,0),     //start speed
                     6,          //mass/radi
                     RGB(255,255,255),  //color
                     150,             //num
                     box            //box
                     );
    items.push_back(next);
    //vars
    Time = TIME;
    T0 = Time;
    begin();
    while(!KEY(VK_ESCAPE)) {
        resetCol();
        clear();
        boxColor();
        txRectangle(box.ldPos.x, box.rpPos.y, box.rpPos.x, box.ldPos.y);
        for(int i =0;i<items.size();i++) {
            items[i].drow();
            items[i].update();
        }
        for(int i=0; i<items.size();i++) {
            for(int j=0; j<items.size();j++) {
                if(i!=j) {
                    if(items[j].isExist && items[i].isExist) {
                        int k = items[i].ballCheck(items[j]);
                        if(k == 1) {
                            items[j].isExist = false;
                            items[i].mass += items[j].mass;
                            items[i].speed += items[j].speed;
                            items[i].radiReCalc();
                        }
                        if(k == 2) {
                            items[i].isExist = false;
                            items[j].mass += items[i].mass;
                            items[j].speed += items[i].speed;
                            items[j].radiReCalc();
                        }
                    }
                }
            }
        }
        gsleep(10);
    }
    end();
    return 0;
}
