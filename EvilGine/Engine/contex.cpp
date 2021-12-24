#include "contex.h"

Contex::Contex(QWidget* parent){
    CreateMap();

    screen = new QLabel(parent);
    fpsLabel = new QLabel(screen);
    fpsLabel->setStyleSheet("QLabel { color : white; }");

    mainCamera.SetPosition(vec3(0,10, 350));

    screen->setGeometry( x, y, width, height);
    screen->show();
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

    SetGeometry( 0, 20, sz.width() - 200, sz.height() - 20);
    screen->setPixmap(QPixmap::fromImage(map));
}

void Contex::OnOpenFile(const QString path){
    qDebug() << "[INF]:> On open file";
    Mesh mesh;

    if(path.contains(".obj")){
        mesh.ReadOBJ(path);
        mainRender.AddMesh(mesh);
        emit AddMesh(mesh);
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

Camera& Contex::GetCamera(){
    return mainCamera;
}

Render& Contex::GetRender(){
    return mainRender;
}
