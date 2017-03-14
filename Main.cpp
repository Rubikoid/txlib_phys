#include "Balls.h"

#define WIDTH 1300
#define HEIGHT 700

int iRand(int min, int max) {
    return min + rand() % (max-min+1);
}

int main(int argc, char* argv[]) {
    //vars
    long Time = 0, T0 = 0;
    vector<ball> items = vector<ball>(0);
    vector<Vector2> dots = vector<Vector2>(0);
    init(WIDTH, HEIGHT);
    Bounds box = Bounds(40,HEIGHT-40,WIDTH-40,40);
    ball next = ball(Vector2(400,200),     //start pos
                     Vector2(2,0),     //start speed
                     Vector2(0,0),     //acc
                     5,          //mass/radi
                     1,          //bounce
                     RGB(255,0,255),  //color
                     1,             //num
                     box            //box
                     );
    items.push_back(next);
    /*next = ball(Vector2(450,425),     //start pos
                     Vector2(0,0),     //start speed
                     20,          //mass/radi
                     RGB(255,0,255),  //color
                     2,             //num
                     box            //box
                     );
    items.push_back(next);*/
    //vars
    Time = TIME;
    T0 = Time;
    begin();
    while(!KEY(VK_ESCAPE)) {
        resetCol();
        clear();
        boxColor();
        txRectangle(box.ldPos.x, box.rpPos.y, box.rpPos.x, box.ldPos.y);
        for(uint i=0;i<dots.size();i++) txSetPixel(dots[i].x, dots[i].y, RGB(0, 255, 0));
        for(uint i =0;i<items.size();i++) {
            dots.push_back(items[i].pos);
            items[i].drow();
            items[i].vecToPos(MouseX(), MouseY());
            items[i].update();
        }
        for(uint i=0; i<items.size();i++) {
            for(uint j=0; j<items.size();j++) {
                if(i!=j) {
                    int k = items[i].ballCheck(items[j]);
                }
            }
        }
        gsleep(1);
    }
    end();
    return 0;
}
