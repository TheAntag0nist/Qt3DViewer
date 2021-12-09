#ifndef MESH_H
#define MESH_H

#include <QRegularExpression>
#include <QStringList>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QFile>
#include <QList>

#include <exception>
#include <iostream>
#include <fstream>
#include <string>

#include "data.h"

enum ROT{
    X,
    Y,
    Z
};

class Mesh
{
public:
    Mesh();
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

private:
    int meshId;
    QString meshName;
    QString format;

    QList<vec3> vertex;
    QList<vec3> normals;
    QList<int> indexFaces;
    QList<int> indexNormals;

    vec3 center;
    vec3 instance;
    mat4 transform;

    void Transform();
    void Parser(QString);

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

private:
    vec3 points[3];
    vec3 center;
    bool is_visible;
};

int GetIndex(QString indexes, int indexNum);

#endif // MESH_H
