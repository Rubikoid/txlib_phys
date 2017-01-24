#ifndef BALLS_H
#define BALLS_H

#include <vector>
#include <string>
#include "grap.h"
#include <stdio.h>

#define TIME		GetTickCount()/100
#define KEY			GetAsyncKeyState
#define uint 		unsigned int //govnokode for compare with vector.size()

using namespace std;
class Vector2 {
    public:
    float x,y;
    Vector2(void) { }

    Vector2(float X, float Y) {
        this->x = X;
        this->y = Y;
    }

    // Returns the length of the vector
    float Length() {
        return sqrt(x * x + y * y);
    }

    float sqrLength() {
        return x * x + y * y;
    }

    // Normalizes the vector
    Vector2 Normalize() {
        Vector2 vector;
        float length = this->Length();

        if(length != 0) {
            vector.x = x/length;
            vector.y = y/length;
        }

        return vector;
    }

    Vector2 negative() {
        return Vector2(x*-1,y*-1);
    }
};

Vector2 operator+(const Vector2 &v1, const Vector2 &v2) {
    return Vector2(v1.x + v2.x, v1.y + v2.y);
}

Vector2 operator-(const Vector2 &v1, const Vector2 &v2) {
    return Vector2(v1.x - v2.x, v1.y - v2.y);
}

Vector2 operator*(const Vector2 &v1, const float &v2) {
    Vector2 result(v1.x*v2,v1.y*v2);
    return result;
}

class base {
    public:
    Vector2 pos, speed;

    base(Vector2 startPos, Vector2 startSpeed) {
        pos = startPos;
        speed = startSpeed;
    }

    base() { }

    void update() {
        if(pos.x+speed.x>800 || pos.x+speed.x<0) {
            pos.x+=speed.x;
            speed.x*=-1;
        }
        else pos.x+=speed.x;
        if(pos.y+pos.y>500 || pos.y+pos.y<0) {
            pos.y+=speed.y;
            speed.y*=-1;
        }
        else pos.y+=speed.y;
    }

    void drow() {
        txSetPixel(pos.x, pos.y, RGB(255,0,0));
    }
};

class ball : public base {
    public:
    float radi;
    COLORREF color;

    int id;
    ball(Vector2 startPos, Vector2 startSpeed, double r=0.0, COLORREF colr = RGB(255,255,255), int ID=0) : base(startPos, startSpeed) {
        radi = r;
        color = colr;
        id = ID;
    }

    ball() : base() {}

    void update() {
        if(800.0-(pos.x+speed.x+radi) < 0 || (pos.x+speed.x-radi) < 0) {
            speed.x*=-1;
        }
        if(500.0-(pos.y+speed.y+radi) < 0 || (pos.y+speed.y-radi) <=0) {
            speed.y*=-1;
        }
        pos.x+=speed.x;
        pos.y+=speed.y;
    }

    void ballCheck(ball &bl)
    {
        Vector2 p12 = pos - bl.pos;
        if(p12.sqrLength() < (radi + bl.radi)*(radi + bl.radi))
        {
            Vector2 tmp = bl.speed;
            bl.speed = speed;
            speed = tmp;
            printf("%d;%d\n",id,bl.id);
            Vector2 p21 = bl.pos - pos, reflDest = p21.Normalize();
            float reflDepth = radi + bl.radi - p21.Length();
            pos = pos + reflDest.negative() * reflDepth;
            bl.pos = bl.pos + reflDest * reflDepth;
        }
    }

    void drow() {
        txSetFillColour(color);
        txSetColor(color, 1);
        txCircle(pos.x, pos.y, radi);
        char a[4];
        sprintf(a,"%d",id);
        resetCol();
        textOut(pos.x,pos.y,a);
    }
};

#endif
