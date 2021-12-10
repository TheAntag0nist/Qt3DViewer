#include "render.h"

Render::Render()
{

}

Render::~Render(){

}

void Render::RenderCamera( Camera camera, QImage* contex){
    // render scene by cam
    vec3 pos = camera.GetPosition();
    vec3 dir = camera.GetDirection();

    for(auto meshIter = meshes.begin(); meshIter != meshes.end(); ++meshIter){
        meshIter->Rotate(X, 0.1);
        meshIter->Rotate(Y, 0.1);
        meshIter->Rotate(Z, 0.1);
        (*meshIter).CreateTriangles();

        auto faces = (*meshIter).GetTriangles();

        for(auto face : faces)
            if(face.IsVisible())
                face.Draw(contex);
    }
}

void Render::AddMesh(Mesh& mesh){
    meshes.push_back(mesh);

    // test
    auto meshIter = meshes.end();
    (*(--meshIter)).Scale(vec3(30,30,30));
    (*meshIter).Move(vec3(200,200,0));
}

void Render::DeleteMesh(const Mesh& mesh){

}

void Render::DeleteMesh(int meshId){

}
