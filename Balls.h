#ifndef BALLS_H
#define BALLS_H

#include <vector>
#include <string>
#include "grap.h"

#define TIME		GetTickCount()/100
#define KEY			GetAsyncKeyState
#define uint 		unsigned int //govnokode for compare with vector.size()

using namespace std;

class base {
    public:
    double x, y;
    double vx, vy;

    base(double startX=0.0, double startY=0.0, double startVX=0.0, double startVY=0.0) {
        x = startX;
        y = startY;
        vx = startVX;
        vy = startVY;
    }

    void update() {
        if(x+vx>800 || x+vx<0) {
            x+=vx;
            vx*=-1;
        }
        else x+=vx;
        if(y+vy>500 || y+vy<0) {
            y+=vy;
            vy*=-1;
        }
        else y+=vy;
    }

    void drow() {
        txSetPixel(x, y, RGB(255,0,0));
        //txCircle(test.x, test.y, test.radi);
    }
};

class ball : public base {
    public:
    double radi;
    COLORREF color;
    ball(double startX=0.0, double startY=0.0, double startVX=0.0, double startVY=0.0, double r=0.0, COLORREF colr = RGB(255,255,255)) : base(startX, startY, startVX, startVY) {
        radi = r;
        color = colr;
    }

    void update() {
        if(800.0-(x+radi) < 0 || (x-radi) < 0) {
            vx*=-1;
            x+=vx;
        }
        else x+=vx;
        if(500.0-(y+radi) < 0 || (y-radi) <=0) {
            vy*=-1;
            y+=vy;
        }
        else y+=vy;
    }

    void drow() {
        txSetFillColour(color);
        txSetColor(color, 1);
        txCircle(x, y, radi);
        resetCol();
    }
};

#endif
