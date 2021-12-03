#ifndef RENDER_H
#define RENDER_H

#include <QObject>
#include <QList>

#include "contex.h"
#include "camera.h"
#include "mesh.h"

class Render : QObject
{
    Q_OBJECT
public:
    Render();
    ~Render();

    QPixmap RenderCamera(Contex contex, Camera camera);

    void AddMesh(Mesh& mesh);
    void DeleteMesh(const Mesh& mesh);
    void DeleteMesh(const int meshId);

private:
    QList<Mesh> meshes;

};

#endif // RENDER_H
