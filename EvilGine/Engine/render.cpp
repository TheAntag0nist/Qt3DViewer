#include "render.h"

Render::Render(){

}

Render::~Render(){

}

void Render::RenderCamera( Camera camera, QImage* contex){
    // render scene by cam
    vec3 camPos = camera.GetPosition();
    vec3 camDir = camera.GetDirection();

    // display
    for(auto meshIter = meshes.begin(); meshIter != meshes.end(); ++meshIter){
        meshIter->Move(vec3(camPos.GetX(),camPos.GetY(), 0));
        vec3 center = meshIter->Center();
        (*meshIter).CreateTriangles();
        auto faces = (*meshIter).GetTriangles();

        for(auto face : faces){
            // draw shadow
            Triangle shadowTriangle;
            vec3 lightPoint = vec3(0, 2500, 40);
            vec3 shadowPoints[3];

            shadowTriangle.IsShadow = true;

            shadowPoints[0].SetX(face.X1().GetX() - face.X1().GetY() / lightPoint.GetY() * lightPoint.GetX());
            shadowPoints[0].SetZ(face.X1().GetZ() - face.X1().GetY() / lightPoint.GetY() * lightPoint.GetZ());

            shadowPoints[1].SetX(face.X2().GetX() - face.X2().GetY() / lightPoint.GetY() * lightPoint.GetX());
            shadowPoints[1].SetZ(face.X2().GetZ() - face.X2().GetY() / lightPoint.GetY() * lightPoint.GetZ());

            shadowPoints[2].SetX(face.X3().GetX() - face.X3().GetY() / lightPoint.GetY() * lightPoint.GetX());
            shadowPoints[2].SetZ(face.X3().GetZ() - face.X3().GetY() / lightPoint.GetY() * lightPoint.GetZ());

            for(int i = 0; i < 3; ++i)
                shadowPoints[i].SetY(-5.5);

            shadowTriangle.SetPoints(shadowPoints);
            shadowTriangle.Draw(contex,camPos);

            // delete invisible faces
            vec3 v1 = face.X1() - face.X2();
            vec3 v2 = face.X3() - face.X2();

            vec3 centerTriangle = face.Center();

            double A = v1.GetY() * v2.GetZ() - v2.GetY() * v1.GetZ();
            double B = v1.GetZ() * v2.GetX() - v2.GetZ() * v1.GetX();
            double C = v1.GetX() * v2.GetY() - v2.GetX() * v1.GetY();
            double D = -(A * face.X1().GetX() + B * face.X1().GetY() + C * face.X1().GetZ());

            if((A * center.GetX() + B * center.GetY() + C * center.GetZ() + D) < 0){
                A *= -1;
                B *= -1;
                C *= -1;
                D *= -1;
            }

            if((A * camPos.GetX() + B * camPos.GetY() + C * camPos.GetZ() + D) > 0){
                face.IsVisible(true);
                face.Draw(contex, camPos);
            }
            else
                face.IsVisible(false);
        }

        vec3 tempCamPos = vec3(0,0,0) - camPos;
        meshIter->Move(vec3(tempCamPos.GetX(),tempCamPos.GetY(), 0));
    }
}

void Render::AddMesh(Mesh& mesh){
    meshes.push_back(mesh);
}

void Render::DeleteMesh(const QString& meshName){
    QList<Mesh>::iterator tempIter;
    for(auto iter = meshes.begin(); iter != meshes.end(); ++iter){
        if(iter->GetName() == meshName){
            tempIter = iter;
            break;
        }
    }

    meshes.erase(tempIter);
}

QList<Mesh>& Render::GetMeshes(){
    return meshes;
}

Mesh& Render::GetMeshByName(const QString& meshName){
    QList<Mesh>::iterator tempIter;
    for(auto iter = meshes.begin(); iter != meshes.end(); ++iter){
        if(iter->GetName() == meshName){
            tempIter = iter;
            break;
        }
    }

    return *tempIter;
}

void Render::CreateShadow(Mesh& mesh){

}
