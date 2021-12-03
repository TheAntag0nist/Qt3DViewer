#include "render.h"

Render::Render()
{

}

Render::~Render(){

}

QPixmap Render::RenderCamera(Contex contex, Camera camera){
    QPixmap map;

    // render scene by cam

    return map;
}

void Render::AddMesh(Mesh& mesh){
    meshes.push_back(mesh);
}

void Render::DeleteMesh(const Mesh& mesh){

}

void Render::DeleteMesh(int meshId){

}
