#include "mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh(){

}

void Mesh::ReadOBJ(QString file){

}

void Mesh::ReadFBX(QString file){

}

QString Mesh::GetName(){
    return meshName;
}

void Mesh::SetName(QString name){
    meshName = name;
}

vec3 Mesh::Center(){
    for(int i = 0; i < vertex.length(); ++i)
        center = center + vertex.at(i);

    center = center / vertex.length();

    return center;
}

void Mesh::Rotate( ROT type, double angle){
    switch (type) {
        case X:
            transform.rotateX(angle);
            break;
        case Y:
            transform.rotateY(angle);
            break;
        case Z:
            transform.rotateZ(angle);
            break;
    }

    Transform();
}

void Mesh::Move(vec3 move){
    transform.move(move);

    Transform();
}

void Mesh::Scale(vec3 s){
    transform.scale(s);

    Transform();
}

void Mesh::Scale(double w){
    transform.scale(w);

    Transform();
}

void Mesh::Transform(){

}
