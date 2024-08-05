// vec.h
typedef struct Vec2 {
    float x, y;
} Vec2;

Vec2 operator+(Vec2 a, Vec2 b) {
    Vec2 c = {
        a.x + b.x,
        a.y + b.y
    };
    return c;
}

Vec2& operator+=(Vec2& a, const Vec2& b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}
