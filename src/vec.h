// vec.h
typedef struct Vector2 {
    float x, y;
} Vector2;

Vector2 operator+(Vector2 a, Vector2 b);


Vector2& operator+=(Vector2& a, const Vector2& b);