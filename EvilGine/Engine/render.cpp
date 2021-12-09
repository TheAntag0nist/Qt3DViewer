#include "render.h"

Render::Render()
{

}

Render::~Render(){

}

static int i = 0;
static bool flag = false;
static float rot = 0.1;
void Render::RenderCamera( Camera camera, QPixmap* contex){
    // render scene by cam
    vec3 pos = camera.GetPosition();
    vec3 dir = camera.GetDirection();

    // draw all
    for(auto mesh : meshes){
        rot += 0.1;
        mesh.Rotate(Y, rot);
        //mesh.Rotate(X, rot);

        mesh.CreateTriangles();

        for(auto face : mesh.GetTriangles())
            if(face.IsVisible())
                face.Draw(contex);
    }
}

void Render::AddMesh(Mesh& mesh){
    meshes.push_back(mesh);
}

void Render::DeleteMesh(const Mesh& mesh){

}

void Render::DeleteMesh(int meshId){

}
