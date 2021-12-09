#ifndef DATA_H
#define DATA_H

#include <cmath>

class vec2;
class vec3;
class vec4;
class mat4;

class vec2
{
public:
    vec2(double v);
    vec2(double x = 0.0f, double y = 0.0f);
    ~vec2();

    void SetX(double);
    void SetY(double);

    double GetX();
    double GetY();

    vec2 Normalize();

    vec2 operator*(double);
    vec2 operator/(double);
    vec2 operator+(double);
    vec2 operator-(double);

    vec2 operator+(vec2);
    vec2 operator-(vec2);

    friend void mswap(vec2&);
    friend void mswap(vec2& ,vec2&);
private:
    double points[2];

};

class vec3{
public:
    vec3(double v);
    vec3(double x = 0.0f, double y = 0.0f, double z = 0.0f);
    ~vec3();

    void SetX(double);
    void SetY(double);
    void SetZ(double);

    double GetX() const;
    double GetY() const;
    double GetZ() const;

    vec2 ToVec2();

    vec3 Normalize();

    vec3 operator*(double);
    vec3 operator/(double);
    vec3 operator+(double);
    vec3 operator-(double);

    vec3 operator+(vec3);
    vec3 operator-(vec3);
    // vec3 operator*(mat4);

private:
    double points[3];

};

class vec4{
public:
    vec4(double v);
    vec4(vec3, double w);
    vec4(double x = 0.0f, double y = 0.0f, double z = 0.0f, double w = 0.0f);
    ~vec4();

    void SetX(double);
    void SetY(double);
    void SetZ(double);
    void SetW(double);

    double GetX() const;
    double GetY() const;
    double GetZ() const;
    double GetW() const;

    vec4 Normalize();

    vec4 operator*(double);
    vec4 operator/(double);
    vec4 operator+(double);
    vec4 operator-(double);

    vec4 operator+(vec4);
    vec4 operator-(vec4);

private:
    double points[4];
};

class mat4{
public:
    mat4();
    ~mat4();
    mat4(const mat4&);

    void create();

    void one();
    void zero();
    void indentity();

    void move(vec3);

    void scale(double w);
    void scale(double x, double y, double z);
    void scale(vec3 s);

    void rotateX(double angle);
    void rotateY(double angle);
    void rotateZ(double angle);

    double* & operator[](const int&) const;
    void operator=(const mat4& second);

    mat4 operator-() const;
    mat4 operator-(const mat4& second);
    mat4 operator+(const mat4& second);
    mat4 operator*(const mat4& second);
    mat4 operator*(const int& num);

    friend vec4 operator*(const mat4 first,const vec3& second);
    friend vec4 operator*(const mat4 first,const vec4& second);

private:
    double **mat;

};

void mswap(vec2&);
void mswap(vec2& ,vec2&);

vec4 operator*(const mat4 first,const vec3& second);
vec4 operator*(const mat4 first,const vec4& second);

#endif // DATA_H
