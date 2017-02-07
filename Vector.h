#ifndef VECTOR_H
#define VECTOR_H

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

#endif
