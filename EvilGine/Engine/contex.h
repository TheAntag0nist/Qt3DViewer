#ifndef CONTEX_H
#define CONTEX_H

#include <QResizeEvent>
#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QTime>

#include "Engine/render.h"

const QColor mainBackgroundColor(40,40,40);
const QSize mainSizeMap(800, 600);

class Contex : public QObject
{
    Q_OBJECT
public:
    Contex(QWidget* parent = nullptr);
    ~Contex();

    void SetGeometry(int x = 0, int y = 0, int w = 0, int h = 0);
    void FillScreen(QColor color);

signals:
    void Resize();
    void Update();

public slots:
    void OnResize(const QSize);
    void OnOpenFile(const QString);
    void RenderLoop();

private:
    QLabel* fpsLabel;
    QLabel* screen;
    QImage map;
    QTime FPS[2];

    bool firstRender;

    Render mainRender;
    Camera mainCamera;

    int width;
    int height;

    int x;
    int y;

    void CreateMap();

};

#endif // CONTEX_H
