#ifndef RENDER_H
#define RENDER_H

#include <limits>

#include <QObject>
#include <QList>

#include "camera.h"
#include "mesh.h"

const QSize mainSize(1600, 800);

class Render : QObject
{
    Q_OBJECT
public:
    Render();
    ~Render();

    void RenderCamera( Camera camera, QImage* contex);

    void AddMesh(Mesh& mesh);
    void DeleteMesh(const Mesh& mesh);
    void DeleteMesh(const int meshId);

private:
    QList<Mesh> meshes;

};

#endif // RENDER_H
