#include "mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh(){

}

void Mesh::ReadOBJ(QString file){
    QFile readFile(file);
    format = "obj";

    if(!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "[ERR]:> Mesh::ReadOBJ(QString);";

    QString allLines = readFile.readAll();
    QStringList lines = allLines.split('\n', Qt::SkipEmptyParts);
    for(int i = 0; i < lines.size(); ++i)
        Parser(lines.at(i));
}

void Mesh::ReadFBX(QString file){
    qDebug() << "[INF]:> FBX will be next feature " << file << ";";
}

void Mesh::Parser(QString line){
    line.replace('\t', ' ');
    line.replace('\n', ' ');
    vec3 ver;

    try{
        if(format == "obj"){
            if(line.contains("v ")){
                QStringList data = line.split(" ", Qt::SkipEmptyParts);

                ver.SetX(data.takeAt(1).toDouble());
                ver.SetY(data.takeAt(1).toDouble());
                ver.SetZ(data.takeAt(1).toDouble());

                vertex.push_back(ver);
            }
            if(line.contains("vn ")){
                QStringList data = line.split(" ", Qt::SkipEmptyParts);

                ver.SetX(data.takeAt(1).toDouble());
                ver.SetY(data.takeAt(1).toDouble());
                ver.SetZ(data.takeAt(1).toDouble());

                normals.push_back(ver);
            }
            if(line.contains("f ")){
                QStringList data = line.split(" ", Qt::SkipEmptyParts);
                int current = 0;

                for(int i = 1; i < data.length(); ++i){
                    // triangulate
                    if(current >= 3){
                        int ind_0 = indexFaces.at(current - 3);
                        int ind_1 = indexFaces.at(current - 1);

                        indexFaces.push_back(ind_0);
                        indexFaces.push_back(ind_1);
                    }

                    int index = GetIndex(data[i], 0);
                    indexFaces.push_back(index);
                    ++current;
                }
            }
        }
    }
    catch(std::exception ex){
        qDebug() << "[ERR]:> " << ex.what() << ";";
    }
}

int GetIndex(QString indexes, int indexNum){
    int i = 0;
    int counter = 0;

    QString info = "";

    while(indexes[i] != '\0' && indexNum != counter){
        if(indexes[i] == '/')
            ++counter;

        ++i;
    }

    while(indexes[i] != '/' && indexes[i] != '\0'){
        info += indexes[i];
        ++i;
    }

    return info.toInt();
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
//========================================
//========================================
Triangle::Triangle(){

}

Triangle::~Triangle(){

}

void Triangle::SetPoints( vec3 pnt_1, vec3 pnt_2, vec3 pnt_3){
    points[0] = pnt_1;
    points[1] = pnt_2;
    points[2] = pnt_3;
}

void Triangle::SetPoints( vec3* pnt){
    // unsafe
    try{
        points[0] = pnt[0];
        points[1] = pnt[1];
        points[2] = pnt[2];
    }
    catch(std::exception& ex){
        qDebug() << "[ERR]:> " << ex.what() << ";";
    }
}

vec3* Triangle::GetPoints(){
    return points;
}

vec3 Triangle::X1(){
    return points[0];
}

vec3 Triangle::X2(){
    return points[1];
}

vec3 Triangle::X3(){
    return points[2];
}

vec3 Triangle::Center(){
    center = (points[0] + points[1] + points[2]) / 3;
    return center;
}
