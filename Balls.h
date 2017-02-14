#ifndef BALLS_H
#define BALLS_H

#include <vector>
#include <string>
#include <stdio.h>
#include <cmath>
#include "TXgrap.h"
#include "Vector.h"

#define TIME		GetTickCount()/100
#define KEY			GetAsyncKeyState
#define uint 		unsigned int //govnokode for compare with vector.size()
#define RADI_MASS   20

using namespace std;

class Bounds {
public:
	Vector2 ldPos, rpPos;

	Bounds(float x1, float y1, float x2, float y2) {
		ldPos = Vector2(x1, y1);
		rpPos = Vector2(x2, y2);
	}

	/*
		������ - 0
		���������� ��� ������ �� x - 2
		���������� ��� ������ �� y - 4
	*/
	int inBounds(Vector2 pos, float radi) {
		int ret = 0;
		if ((pos.x + radi) > rpPos.x || (pos.x - radi) < ldPos.x) { ret = ret | 2; }
		if ((pos.y + radi) > ldPos.y || (pos.y - radi) < rpPos.y) { ret = ret | 4; }
		return ret;
	}
	Bounds() {}
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
		int posCheck = bounds.inBounds(pos + speed, 1);
		if ((posCheck & 2) == 2) speed.x *= -1;
		if ((posCheck & 4) == 4) speed.y *= -1;
		pos += speed;
	}

	void drow() {
		txSetPixel(pos.x, pos.y, RGB(255, 0, 0));
	}
};

class ball : public base {
public:
	float radi;
	float mass;

	bool isExist;
	COLORREF color;

	int id;
	ball(Vector2 startPos, Vector2 startSpeed, float r = 0.0, COLORREF colr = RGB(255, 255, 255), int ID = 0, Bounds bnds = Bounds(0, 0, 0, 0)) : base(startPos, startSpeed, bnds) {
		color = colr;
		id = ID;
		mass = r;
		radiReCalc();
	}

	ball() : base() {}

	void update() {
		int posCheck = bounds.inBounds(pos + speed, radi);
		if ((posCheck & 2) == 2) speed.x *= -1;
		if ((posCheck & 4) == 4) speed.y *= -1;
		pos += speed;
	}

	int ballCheck(ball &bl)
	{
		Vector2 p12 = pos - bl.pos;
		if (p12.sqrLength() < (radi + bl.radi)*(radi + bl.radi)) {
			//Vector2 oldSpeed = speed, blOldSpeed = bl.speed;
			//speed = oldSpeed * ((mass - bl.mass)/(mass+bl.mass)) + blOldSpeed * ((2*bl.mass)/(mass+bl.mass)); //����� �������� � ���������
			//bl.speed = oldSpeed * ((2*mass)/(mass+bl.mass)) + blOldSpeed * ((bl.mass - mass)/(mass+bl.mass));
			/*
				v1 = v1old * (m1 - m2)/(m1 + m2) + v2old * (2 * m2)/(m1 + m2)
				v2 = v1old * (2 * m1)/(m1 + m2) + v2old * (m2 - m1)/(m1+m2)
			*/
			Vector2 p21 = bl.pos - pos, reflDest = p21.Normalize(), v21 = bl.speed - speed;
			float f = mass / (mass + bl.mass) * 0.5f;
			speed += reflDest.negative() * f;
			bl.speed += reflDest * f;
			float reflDepth = radi + bl.radi - p21.Length();
			pos += reflDest.negative() * reflDepth * 0.5; // ������������ ������ �� �� �������.
			bl.pos += reflDest * reflDepth * 0.5;
		}
		return 0;
	}

	void drow() {
		txSetFillColour(color);
		txSetColor(color, 1);
		txCircle(pos.x, pos.y, radi);
		char a[4];
		sprintf(a, "%d", id);
		resetCol();
		textOut(pos.x, pos.y, a);
		txLine(pos.x, pos.y, speed.x * 20 + pos.x, speed.y * 20 + pos.y);
	}

	void radiReCalc() {
		//4*pi*r^3 = m
		radi = pow((mass / (4 * M_PI)), 1.0 / 3.0) * RADI_MASS;
	}
};

#endif
