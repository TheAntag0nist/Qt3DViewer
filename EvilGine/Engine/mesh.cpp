#include "mesh.h"

Mesh::Mesh(){
    transform.create();
}

Mesh::Mesh(const Mesh& obj){
    this->meshId = obj.meshId;
    this->meshName = obj.meshName;
    this->triangles = obj.triangles;
    this->vertex = obj.vertex;
    this->normals = obj.normals;
    this->indexFaces = obj.indexFaces;
    this->indexNormals = obj.indexNormals;

    this->center = obj.center;
    this->instance = obj.instance;
    this->transform = obj.transform;
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
                        int ind_0 = indexFaces.at(indexFaces.length() - 3);
                        int ind_1 = indexFaces.at(indexFaces.length() - 1);

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
    center  = vec3(0,0,0);
    for(int i = 0; i < vertex.size(); ++i)
        center = center + vertex.at(i);

    center = center / vertex.size();

    return center;
}

void Mesh::Rotate( ROT type, double angle){
    transform.indentity();
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
    transform.indentity();
    transform.move(move);
    moveFlag = true;

    Transform();
}

void Mesh::Scale(vec3 s){
    transform.indentity();
    transform.scale(s);

    Transform();
}

void Mesh::Scale(double w){
    transform.indentity();
    transform.scale(w);

    Transform();
}

void Mesh::SetTransform(const mat4 mat){
    this->transform = mat;
}

void Mesh::CreateTriangles(){
    triangles.clear();

    int currentVertex = 0;
    Triangle triangle;
    vec3 points[3];

    for(auto item : indexFaces){
        points[currentVertex++] = vertex.at(item - 1);

        if(currentVertex % 3 == 0){
            triangle.SetPoints(points);
            triangles.push_back(triangle);
            currentVertex = 0;
        }
    }
}

void Mesh::Transform(){
    this->Center();
    vec4 tempVertex;

    for(auto ver = vertex.begin(); ver != vertex.end(); ++ver){
        auto vec = (moveFlag) ?  *ver : (*ver - center);
        tempVertex = transform * vec;

        double w = tempVertex.GetW();

        (*ver).SetX(tempVertex.GetX() / w);
        (*ver).SetY(tempVertex.GetY() / w);
        (*ver).SetZ(tempVertex.GetZ() / w);

        (*ver) = moveFlag ? *ver : *ver + center;
    }

    moveFlag = false;
}

QList<Triangle>& Mesh::GetTriangles(){
    return triangles;
}

//==========================================
//==========================================
Line::Line(){

}

Line::Line(vec2 pnt_1, vec2 pnt_2){
    points[0] = pnt_1;
    points[1] = pnt_2;
}

Line::~Line(){

}

// Brezenhem line drawing
void Line::DrawLine( QImage* map, vec2 pnt_1, vec2 pnt_2){
    // check line points
    this->points[0] = pnt_1;
    this->points[1] = pnt_2;

    // double eqauls errors can be
    // dangerous code here!!
    if (points[0].GetX() == points[1].GetX() && points[0].GetY() == points[1].GetY()) {
        map->setPixel( points[0].GetX(), points[0].GetY(), mainWireframeColor.rgba());
        return;
    }

    auto steep = abs((points[1].GetY()  - points[0].GetY())) > abs((points[1].GetX()  - points[0].GetX()));

    if(steep){
        double temp = points[0].GetX();

        points[0].SetX(points[0].GetY());
        points[0].SetY(temp);

        temp = points[1].GetX();

        points[1].SetX(points[1].GetY());
        points[1].SetY(temp);
    }

    if (points[0].GetX() > points[1].GetX()){
        double temp = points[0].GetX();

        points[0].SetX(points[1].GetX());
        points[1].SetX(temp);

        temp = points[0].GetY();

        points[0].SetY(points[1].GetY());
        points[1].SetY(temp);
    }

    int dx = points[1].GetX() - points[0].GetX();
    int dy = abs(points[1].GetY() - points[0].GetY());
    int error = dx / 2;
    int ystep = (points[0].GetY() < points[1].GetY()) ? 1 : -1;
    int y = points[0].GetY();

    for(int x = points[0].GetX(); x <= points[1].GetX(); ++x){
        if(x > 0 && y > 0 && x < 800 && y < 600)
            map->setPixel( steep ? y : x, steep ? x : y, mainWireframeColor.rgba());
        else
            break;

        error -= dy;

        if(error < 0){
            y += ystep;
            error += dx;
        }
    }
}

void Line::SetPoints(vec2 first, vec2 second){
    this->points[0] = first;
    this->points[1] = second;
}

void Line::SetPoints(vec2* pnt){
    this->points[0] = pnt[0];
    this->points[1] = pnt[1];
}

vec2* Line::GetPoints(){
    return this->points;
}
//========================================
//========================================
Triangle::Triangle(){
    is_visible = true;
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

bool Triangle::IsVisible(){
    return is_visible;
}

void Triangle::IsVisible(bool vis){
    this->is_visible = vis;
}

// draw trianle
void Triangle::Draw(QImage* map){
    Line ln;

    ln.DrawLine(map, points[0].ToVec2(), points[1].ToVec2());
    ln.DrawLine(map, points[1].ToVec2(), points[2].ToVec2());
    ln.DrawLine(map, points[2].ToVec2(), points[0].ToVec2());

    Center();
    // FloodFill( map, mainWireframeColor);
}

void Triangle::FloodFill(QImage* map,QColor color){
    QStack<vec2> fillStack;
    fillStack.push(center.ToVec2());

    auto mainColor = mainWireframeColor.rgba();
    if((points[0].GetX() == points[1].GetX() && points[1].GetX() == points[2].GetX()) ||
            (points[0].GetY() == points[1].GetY() && points[1].GetY() == points[2].GetY()))
        return;

    while(!fillStack.isEmpty()){
        vec2 point = fillStack.pop();
        map->setPixel(point.GetX(), point.GetY(), color.rgba());

        auto temp = GetPixel(map, point.GetX() + 1, point.GetY()).rgba();
        auto temp_1 = GetPixel(map, point.GetX(), point.GetY() + 1).rgba();
        auto temp_2 = GetPixel(map, point.GetX() - 1, point.GetY()).rgba();
        auto temp_3 = GetPixel(map, point.GetX(), point.GetY() - 1).rgba();

        if(temp != mainColor)
                fillStack.push(vec2(point.GetX() + 1, point.GetY()));
        if(temp_1 != mainColor)
                fillStack.push(vec2(point.GetX(), point.GetY() + 1));
        if(temp_2 != mainColor)
                fillStack.push(vec2(point.GetX() - 1, point.GetY()));
        if(temp_3 != mainColor)
                fillStack.push(vec2(point.GetX(), point.GetY() - 1));
    }
}


QColor Triangle::GetPixel(QImage* img, int x, int y){
    if(x > 0 && y > 0 && x < 800 && y < 600){
        QRgb *rowData = (QRgb*)img->scanLine(x);
        QRgb pixelData = rowData[y];

        return QColor(pixelData);
    }

    return mainWireframeColor;
}
