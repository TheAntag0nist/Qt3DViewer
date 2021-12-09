#include "render.h"

Render::Render()
{

}

Render::~Render(){

}

QPixmap Render::RenderCamera( Camera camera){
    QPixmap* map = new QPixmap(mainSize);

    // render scene by cam
    vec3 pos = camera.GetPosition();
    vec3 dir = camera.GetDirection();



    return *map;
}

void Render::AddMesh(Mesh& mesh){
    meshes.push_back(mesh);
}

void Render::DeleteMesh(const Mesh& mesh){

}

void Render::DeleteMesh(int meshId){

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
void Line::DrawLine( QPixmap* map, vec2 pnt_1, vec2 pnt_2){
    QImage img = map->toImage();

    // check line points
    this->points[0] = pnt_1;
    this->points[1] = pnt_2;

    // double eqauls errors can be
    // dangerous code here!!
    if (points[0].GetX() == points[1].GetX() && points[0].GetY() == points[1].GetY()) {
        img.setPixel( points[0].GetX(), points[0].GetY(), mainWireframeColor.rgba());
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
        img.setPixel( steep ? y : x, steep ? x : y, mainWireframeColor.rgba());
        error -= dy;
        if(error < 0){
            y += ystep;
            error += dx;
        }
    }

    *map = QPixmap::fromImage(img);
}
