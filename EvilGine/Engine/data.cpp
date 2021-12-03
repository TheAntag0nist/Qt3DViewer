#include "data.h"

vec2::vec2(double v){
    points[0] = v;
    points[1] = v;
}

vec2::vec2(double x, double y){
    points[0] = x;
    points[1] = y;
}

vec2::~vec2(){
    points[0] = 0.0f;
    points[1] = 0.0f;
}

void vec2::SetX(double x){
    this->points[0] = x;
}

void vec2::SetY(double y){
    this->points[0] = y;
}

double vec2::GetX(){
    return points[0];
}

double vec2::GetY(){
    return points[1];
}

vec2 vec2::Normalize(){
    vec2 tmp;

    double inv = 1.0f / sqrt(points[0]*points[0]
            + points[1]*points[1]);

    return tmp / inv;
}

vec2 vec2::operator*(double val){
    vec2 tmp = *this;

    tmp.points[0] *= val;
    tmp.points[1] *= val;

    return tmp;
}

vec2 vec2::operator/(double val){
    vec2 tmp = *this;

    tmp.points[0] /= val;
    tmp.points[1] /= val;

    return tmp;
}

vec2 vec2::operator+(double val){
    vec2 tmp = *this;

    tmp.points[0] += val;
    tmp.points[1] += val;

    return tmp;
}

vec2 vec2::operator-(double val){
    vec2 tmp = *this;

    tmp.points[0] -= val;
    tmp.points[1] -= val;

    return tmp;
}

vec2 vec2::operator+(vec2 second){
    vec2 tmp = *this;

    tmp.points[0] += second.points[0];
    tmp.points[1] += second.points[1];

    return tmp;
}

vec2 vec2::operator-(vec2 second){
    vec2 tmp = *this;

    tmp.points[0] -= second.points[0];
    tmp.points[1] -= second.points[1];

    return tmp;
}
//=======================================================
//=======================================================
vec3::vec3(double v){
    points[0] = v;
    points[1] = v;
    points[2] = v;
}

vec3::vec3(double x, double y, double z){
    points[0] = x;
    points[1] = y;
    points[2] = z;
}

vec3::~vec3(){
    points[0] = 0.0f;
    points[1] = 0.0f;
    points[2] = 0.0f;
}

void vec3::SetX(double x){
    this->points[0] = x;
}

void vec3::SetY(double y){
    this->points[1] = y;
}

void vec3::SetZ(double z){
    this->points[2] = z;
}

double vec3::GetX(){
    return points[0];
}

double vec3::GetY(){
    return points[1];
}

double vec3::GetZ(){
    return points[2];
}

vec3 vec3::Normalize(){
    vec3 tmp;

    double inv = 1.0f / sqrt(points[0]*points[0]
            + points[1]*points[1] + points[2]*points[2]);

    return tmp / inv;
}

vec3 vec3::operator*(double val){
    vec3 tmp = *this;

    tmp.points[0] *= val;
    tmp.points[1] *= val;
    tmp.points[2] *= val;

    return tmp;
}

vec3 vec3::operator/(double val){
    vec3 tmp = *this;

    tmp.points[0] /= val;
    tmp.points[1] /= val;
    tmp.points[2] /= val;

    return tmp;
}

vec3 vec3::operator+(double val){
    vec3 tmp = *this;

    tmp.points[0] += val;
    tmp.points[1] += val;
    tmp.points[2] += val;

    return tmp;
}

vec3 vec3::operator-(double val){
    vec3 tmp = *this;

    tmp.points[0] -= val;
    tmp.points[1] -= val;
    tmp.points[2] -= val;

    return tmp;
}

vec3 vec3::operator+(vec3 second){
    vec3 tmp = *this;

    tmp.points[0] += second.points[0];
    tmp.points[1] += second.points[1];
    tmp.points[2] += second.points[2];

    return tmp;
}

vec3 vec3::operator-(vec3 second){
    vec3 tmp = *this;

    tmp.points[0] -= second.points[0];
    tmp.points[1] -= second.points[1];
    tmp.points[2] -= second.points[2];

    return tmp;
}
//=======================================================
//=======================================================
vec4::vec4(double v){
    points[0] = v;
    points[1] = v;
    points[2] = v;
    points[3] = v;
}

vec4::vec4(vec3 v, double w){
    points[0] = v.GetX();
    points[1] = v.GetY();
    points[2] = v.GetZ();
    points[3] = w;
}

vec4::vec4(double x, double y, double z, double w){
    points[0] = x;
    points[1] = y;
    points[2] = z;
    points[3] = w;
}

vec4::~vec4(){
    points[0] = 0.0f;
    points[1] = 0.0f;
    points[2] = 0.0f;
    points[3] = 1.0f;
}

void vec4::SetX(double x){
    this->points[0] = x;
}

void vec4::SetY(double y){
    this->points[1] = y;
}

void vec4::SetZ(double z){
    this->points[2] = z;
}

void vec4::SetW(double z){
    this->points[3] = z;
}

double vec4::GetX(){
    return points[0];
}

double vec4::GetY(){
    return points[1];
}

double vec4::GetZ(){
    return points[2];
}

double vec4::GetW(){
    return points[3];
}

vec4 vec4::Normalize(){
    vec4 tmp;

    double inv = 1.0f / sqrt(points[0]*points[0]
            + points[1]*points[1] + points[2]*points[2]);

    return tmp / inv;
}

vec4 vec4::operator*(double val){
    vec4 tmp = *this;

    tmp.points[0] *= val;
    tmp.points[1] *= val;
    tmp.points[2] *= val;
    tmp.points[3] *= val;

    return tmp;
}

vec4 vec4::operator/(double val){
    vec4 tmp = *this;

    tmp.points[0] /= val;
    tmp.points[1] /= val;
    tmp.points[2] /= val;
    tmp.points[3] /= val;

    return tmp;
}

vec4 vec4::operator+(double val){
    vec4 tmp = *this;

    tmp.points[0] += val;
    tmp.points[1] += val;
    tmp.points[2] += val;
    tmp.points[3] += val;

    return tmp;
}

vec4 vec4::operator-(double val){
    vec4 tmp = *this;

    tmp.points[0] -= val;
    tmp.points[1] -= val;
    tmp.points[2] -= val;
    tmp.points[3] -= val;

    return tmp;
}

vec4 vec4::operator+(vec4 second){
    vec4 tmp = *this;

    tmp.points[0] += second.points[0];
    tmp.points[1] += second.points[1];
    tmp.points[2] += second.points[2];
    tmp.points[3] += second.points[3];

    return tmp;
}

vec4 vec4::operator-(vec4 second){
    vec4 tmp = *this;

    tmp.points[0] -= second.points[0];
    tmp.points[1] -= second.points[1];
    tmp.points[2] -= second.points[2];
    tmp.points[3] -= second.points[3];

    return tmp;
}
//=======================================================
//=======================================================
mat4::mat4(){
    mat = new double* [4];
    for(int i = 0; i < 4; ++i)
        mat[i] = new double[4];

    this->zero();
}

mat4::~mat4(){
    if(mat == nullptr)
        return;

    for(int i = 0; i < 4; ++i)
        delete mat[i];

    delete mat;
}

mat4::mat4(const mat4& second){
    this->~mat4();
    mat = new double* [4];
    for(int i = 0; i < 4; ++i)
        mat[i] = new double[4];

    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            mat[i][j] = second[i][j];
}

double* & mat4::operator[](const int& i) const{
    return mat[i];
}

void mat4::operator=(const mat4& second){
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            mat[i][j] = second[i][j];
}

mat4 mat4::operator-() const{
    mat4 temp;

    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            temp.mat[i][j] = -mat[i][j];

    return temp;
}

mat4 mat4::operator+(const mat4& second){
    mat4 temp;

    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            temp.mat[i][j] = mat[i][j] + second.mat[i][j];

    return temp;
}

mat4 mat4::operator*(const mat4& second){
    mat4 temp;

    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j){
            for(int k=0; k < 4; k++)
                temp[i][j] = mat[i][k] * second[k][j];
        }

    return temp;
}

mat4 mat4::operator*(const int& num){
    mat4 temp;

    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            temp.mat[i][j] = mat[i][j] * num;

    return temp;
}

void mat4::one(){
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            mat[i][j] = 1.0f;
}

void mat4::zero(){
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            mat[i][j] = 0.0f;
}

void mat4::indentity(){
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j){
            mat[i][j] = 0.0f;

            if(i == j)
                mat[i][j] = 1.0f;
        }
}

void mat4::move(vec3 move){
    mat[0][3] = move.GetX();
    mat[1][3] = move.GetY();
    mat[2][3] = move.GetZ();
}

void mat4::scale(double w){
    mat[3][3] = w;
}

void mat4::scale(double x, double y, double z){
    mat[0][0] = x;
    mat[1][1] = y;
    mat[2][2] = z;
}

void mat4::scale(vec3 s){
    mat[0][0] = s.GetX();
    mat[1][1] = s.GetY();
    mat[2][2] = s.GetZ();
}

void mat4::rotateX(double angle){
    mat[1][1] = cos(angle);
    mat[1][2] = -sin(angle);
    mat[2][1] = sin(angle);
    mat[2][2] = cos(angle);
}

void mat4::rotateY(double angle){
    mat[0][0] = cos(angle);
    mat[0][2] = sin(angle);
    mat[2][1] = -sin(angle);
    mat[2][2] = cos(angle);
}

void mat4::rotateZ(double angle){
    mat[0][0] = cos(angle);
    mat[0][1] = -sin(angle);
    mat[1][0] = sin(angle);
    mat[1][1] = cos(angle);
}
