#ifndef CONTEX_H
#define CONTEX_H

#include <QResizeEvent>
#include <QWidget>
#include <QObject>
#include <QLabel>

class Contex : QObject
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

private:
    QLabel* screen;
    QPixmap map;

    int width;
    int height;

    int x;
    int y;

};

#endif // CONTEX_H
