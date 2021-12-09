#ifndef RENDER_H
#define RENDER_H

#include <limits>

#include <QObject>
#include <QList>

#include "contex.h"
#include "camera.h"
#include "mesh.h"

const QSize mainSize(1600, 800);
const QColor mainWireframeColor(160,160,160);

class Render : QObject
{
    Q_OBJECT
public:
    Render();
    ~Render();

    QPixmap RenderCamera( Camera camera);

    void AddMesh(Mesh& mesh);
    void DeleteMesh(const Mesh& mesh);
    void DeleteMesh(const int meshId);

private:
    QList<Mesh> meshes;

};

class Line{
public:
    Line();
    Line(vec2, vec2);
    ~Line();

    void DrawLine( QPixmap*, vec2, vec2);

private:
    vec2 points[2];
    vec2 center;

};

#endif // RENDER_H
