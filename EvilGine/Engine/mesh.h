#ifndef MESH_H
#define MESH_H

#include <QRegularExpression>
#include <QStringList>
#include <QPixmap>
#include <QString>
#include <QObject>
#include <QVector>
#include <QImage>
#include <QDebug>
#include <QStack>
#include <QFile>
#include <QList>

#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <float.h>

#include "data.h"

const QColor mainWireframeColor(160,160,160);
const double fov = 1.57;
const double far = 1000;
const double near = 400;

static double aspect = 0.0;
static mat4 projectionMatrix;
static vec3 defaultValueVec3 = vec3(-DBL_MAX, -DBL_MAX, -DBL_MAX);

class Mesh;
class Line;
class Triangle;

class Mesh
{
public:
    Mesh();
    Mesh(const Mesh&);
    ~Mesh();

    void ReadOBJ(QString file);
    void ReadFBX(QString file);

    QString GetName();
    void SetName(QString);

    vec3 GetInstace(vec3);
    void SetInstance();

    vec3 Center();
    void Move(vec3);
    void Scale(vec3);
    void Scale(double);
    void Rotate( ROT, double);
    void Rotate( ROT, double, vec3);

    void Transform(vec3 point = defaultValueVec3);
    void CreateTriangles();
    void SetTransform(const mat4);
    QList<Triangle>& GetTriangles();

private:
    int meshId;
    QString meshName;
    QString format;

    QList<Triangle> triangles;

    QVector<vec3> vertex;
    QVector<vec3> normals;
    QVector<int> indexFaces;
    QVector<int> indexNormals;

    vec3 center;
    vec3 instance;
    mat4 transform;

    bool moveFlag;

    void Parser(QString);
    QString GetName(QString);

};
//========================================
//========================================
class Line{
public:
    Line();
    Line(vec2, vec2);
    ~Line();

    void DrawLine( QImage*, vec2, vec2, QColor color = mainWireframeColor);

    void SetPoints(vec2, vec2);
    void SetPoints(vec2*);

    vec2* GetPoints();

private:
    vec2 points[2];
    vec2 center;

};
//========================================
//========================================
class Triangle{
public:
    Triangle();
    ~Triangle();

    void SetPoints( vec3, vec3, vec3);
    void SetPoints( vec3*);
    vec3* GetPoints();

    vec3 X1();
    vec3 X2();
    vec3 X3();

    vec3 Center();

    bool IsVisible();
    void IsVisible(bool);

    void Draw(QImage*, vec3& camPos);
    void FloodFill(QImage*, QColor, vec2 point = vec2(-1,-1));
    QColor GetPixel(QImage*, int, int);

    vec2 Projection(QImage* map,vec3 cam, vec3 point);

    bool IsShadow;

private:
    vec3 points[3];
    vec3 center;
    vec2 pnt[3];

    bool is_visible;

};

int GetIndex(QString indexes, int indexNum);

#endif // MESH_H
