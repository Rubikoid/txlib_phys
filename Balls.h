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

Vector2 operator+=(Vector2 &v1, const Vector2 &v2) {
    v1 = v1 + v2;
    return v1;
}

Vector2 operator-(const Vector2 &v1, const Vector2 &v2) {
    return Vector2(v1.x - v2.x, v1.y - v2.y);
}

Vector2 operator*(const Vector2 &v1, const float &v2) {
    Vector2 result(v1.x*v2,v1.y*v2);
    return result;
}

float operator*(const Vector2 &v1, const Vector2 &v2) {
    float result = v1.x*v2.x + v1.y+v2.y;
    return result;
}

class Bounds {
    public:
    Vector2 ldPos, rpPos;

    Bounds(float x1,float y1, float x2, float y2) {
        ldPos = Vector2(x1,y1);
        rpPos = Vector2(x2,y2);
    }

    /*
        внутри - 0
        пересекает или больше по x - 2
        пересекает или больше по y - 4
    */
    int inBounds(Vector2 pos, float radi) {
        int ret = 0;
        if((pos.x+radi) > rpPos.x || (pos.x-radi) < ldPos.x){ ret = ret | 2; }
        if((pos.y+radi) > ldPos.y || (pos.y-radi) < rpPos.y){ ret = ret | 4; }
        return ret;
    }
    Bounds(){}
};

class base {
    public:
    Vector2 pos, speed;
    Bounds bounds;

    base(Vector2 startPos, Vector2 startSpeed, Bounds bnds) {
        pos = startPos;
        speed = startSpeed;
        bounds = bnds;
    }

    base() { }

    void update() {
        int posCheck = bounds.inBounds(pos+speed,1);
        if(posCheck & 2) speed.x*=-1;
        if(posCheck & 4) speed.y*=-1;
        pos += speed;
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
    ball(Vector2 startPos, Vector2 startSpeed, double r=0.0, COLORREF colr = RGB(255,255,255), int ID=0, Bounds bnds = Bounds(0,0,0,0)) : base(startPos, startSpeed, bnds) {
        radi = r;
        color = colr;
        id = ID;
    }

    ball() : base() {}

    void update() {
        int posCheck = bounds.inBounds(pos+speed,radi);
        if(posCheck == 2) speed.x*=-1;
        if(posCheck == 4){ printf("aa"); speed.y*=-1; }
        if(posCheck != 0) {printf("x:%d,y:%d\n",posCheck & 2, posCheck & 4);}
        pos += speed;
    }

    void ballCheck(ball &bl)
    {
        Vector2 p12 = pos - bl.pos;
        if(p12.sqrLength() < (radi + bl.radi)*(radi + bl.radi))
        {
            printf("%d;%d\n",id,bl.id);
            Vector2 oldSpeed = speed, blOldSpeed = bl.speed;
            speed = oldSpeed * ((radi - bl.radi)/(radi+bl.radi)) + blOldSpeed * ((2*bl.radi)/(radi+bl.radi)); //новая скорость с импульсом
            bl.speed = oldSpeed * ((2*radi)/(radi+bl.radi)) + blOldSpeed * ((bl.radi - radi)/(radi+bl.radi));

            Vector2 p21 = bl.pos - pos, reflDest = p21.Normalize();
            float reflDepth = radi + bl.radi - p21.Length();
            pos += reflDest.negative() * reflDepth * 0.5; // расталкиваем шарики по их центрам.
            bl.pos += reflDest * reflDepth * 0.5;
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
