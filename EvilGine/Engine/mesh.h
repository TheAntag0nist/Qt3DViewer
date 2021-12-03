#ifndef MESH_H
#define MESH_H

#include <QObject>
#include <QList>

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

    QList<vec3> vertex;
    QList<vec3> normals;
    QList<QList<int>> faces;

    vec3 center;
    vec3 instance;
    mat4 transform;

    void Transform();

};

#endif // MESH_H
