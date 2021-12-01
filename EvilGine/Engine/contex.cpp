#include "contex.h"

Contex::Contex(QWidget* parent)
{
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

    screen->setGeometry( this->x, this->y, width, height);
}

void Contex::FillScreen(QColor color){
    QPixmap* map = new QPixmap(width, height);
    map->fill(color);

    screen->setPixmap(*map);
    delete map;
}

void Contex::OnResize(const QSize sz){
    // set new size for screen
    screen->setGeometry( x, y, sz.width(), sz.height());

    QPixmap* map = new QPixmap(sz);
    map->fill(QColor(40,40,40));

    screen->setPixmap(*map);
    delete map;
}
