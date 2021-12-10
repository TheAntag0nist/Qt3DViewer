#include "contex.h"

Contex::Contex(QWidget* parent){
    CreateMap();

    screen = new QLabel(parent);
    fpsLabel = new QLabel(screen);
    fpsLabel->setStyleSheet("QLabel { color : white; }");

    screen->setGeometry( x, y, width, height);
    screen->show();

    // test load and add to render
    Mesh mesh;
    mesh.ReadOBJ("C:\\Users\\teoru\\_projects\\.MY_PRJ\\EvilGine\\.TestOBJ\\cube.obj");
    mainRender.AddMesh(mesh);

    mainRender.RenderCamera(mainCamera, &map);
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
    map = map.scaled(width, height);
}

void Contex::FillScreen(QColor color){
    map.fill(color);
    screen->setPixmap(QPixmap::fromImage(map));
}

void Contex::OnResize(const QSize sz){
    // set fps label
    fpsLabel->setGeometry( screen->width() - 60, 0, 60, 20);
    FillScreen(mainBackgroundColor);

    // render after set geometry
    // infuenc on scale
    mainRender.RenderCamera(mainCamera, &map);

    SetGeometry(0, 20, sz.width(), sz.height() - 20);
    screen->setPixmap(QPixmap::fromImage(map));
}

void Contex::OnOpenFile(const QString path){
    qDebug() << "[INF]:> On open file";
    Mesh mesh;

    if(path.contains(".obj")){
        mesh.ReadOBJ(path);
        mainRender.AddMesh(mesh);
    }
}

void Contex::RenderLoop(){
    FPS[1] = QTime::currentTime();
    fpsLabel->setText("FPS: " + QString::number(( 1.0f / (FPS[1].msec() - FPS[0].msec())) * 1000));

    FillScreen(mainBackgroundColor);
    mainRender.RenderCamera(mainCamera, &map);
    screen->setPixmap(QPixmap::fromImage(map));

    FPS[0] = FPS[1];
}

void Contex::CreateMap(){
    QPixmap* tempMap = new QPixmap(mainSizeMap);
    map = tempMap->toImage();
}
