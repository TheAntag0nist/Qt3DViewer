#include "contex.h"

Contex::Contex(QWidget* parent)
{
    map = new QPixmap(mainSizeMap);
    screen = new QLabel(parent);
    screen->setGeometry( x, y, width, height);

    screen->show();

    // test load and add to render
    Mesh mesh;
    mesh.ReadOBJ("C:\\Users\\teoru\\_projects\\.MY_PRJ\\EvilGine\\.TestOBJ\\cube.obj");
    mainRender.AddMesh(mesh);

    mainRender.RenderCamera(mainCamera, map);
}

Contex::~Contex(){
    delete screen;
}

void Contex::SetGeometry(int x, int y, int w, int h){
    this->x = x;
    this->y = y;

    this->width = w;
    this->height = h;

    screen->setGeometry( x, y, width, height);
    *map = map->scaled(width, height);
}

void Contex::FillScreen(QColor color){
    map->fill(color);
    screen->setPixmap(*map);
}

void Contex::OnResize(const QSize sz){
    RecreateMap();
    FillScreen(mainBackgroundColor);

    Line test;

    /*
    test.DrawLine(map,vec2(10 + delta,10 + delta), vec2(20 + delta,300 + delta));
    test.DrawLine(map,vec2(20 + delta,300 + delta), vec2(70 + delta,5 + delta));
    test.DrawLine(map,vec2(70 + delta,5 + delta), vec2(10 + delta,10 + delta));

    // test 1
    // 1. good
    test.DrawLine(map, vec2(10,50), vec2(10,10));
    // 2. good
    test.DrawLine(map, vec2(50,10), vec2(10,10));

    // test 2
    // 1. good
    test.DrawLine(map, vec2(50,10), vec2(50,50));
    // 2. good
    test.DrawLine(map, vec2(50,50), vec2(10,50));
    */

    mainRender.RenderCamera(mainCamera, map);

    SetGeometry(0, 0, sz.width(), sz.height());
    screen->setPixmap(*map);
}


void Contex::RecreateMap(){
    if(map != nullptr)
        delete map;
    map = new QPixmap(mainSizeMap);
}
