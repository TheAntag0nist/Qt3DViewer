#ifndef MESH_H
#define MESH_H

#include <QRegularExpression>
#include <QPixmap>
#include <QImage>
#include <QStringList>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QFile>
#include <QList>
#include <QStack>

#include <exception>
#include <iostream>
#include <fstream>
#include <string>

#include "data.h"

const QColor mainWireframeColor(160,160,160);

enum ROT{
    X,
    Y,
    Z
};

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
    void Rotate( ROT, double);
    void Move(vec3);
    void Scale(vec3);
    void Scale(double);

    void SetTransform(const mat4);
    void CreateTriangles();
    QList<Triangle>& GetTriangles();
    void Transform();

private:
    int meshId;
    QString meshName;
    QString format;

    QList<Triangle> triangles;

    QList<vec3> vertex;
    QList<vec3> normals;
    QList<int> indexFaces;
    QList<int> indexNormals;

    vec3 center;
    vec3 instance;
    mat4 transform;

    bool moveFlag;

    void Parser(QString);

};
//========================================
//========================================
class Line{
public:
    Line();
    Line(vec2, vec2);
    ~Line();

    void DrawLine( QPixmap*, vec2, vec2);

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

    void Draw(QPixmap*);
    void FloodFill(QPixmap*, QColor);
    QColor GetPixel(QImage, int, int);

private:
    vec3 points[3];
    vec3 center;

    bool is_visible;
};

int GetIndex(QString indexes, int indexNum);

#endif // MESH_H
