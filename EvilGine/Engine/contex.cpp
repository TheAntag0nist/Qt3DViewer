#include "contex.h"

Contex::Contex(QWidget* parent)
{
    map = QPixmap(800, 600);
    screen = new QLabel(parent);
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
    screen->setPixmap(map);
}

void Contex::OnResize(const QSize sz){
    SetGeometry(0, 0, sz.width(), sz.height());

    screen->setPixmap(map);
}
