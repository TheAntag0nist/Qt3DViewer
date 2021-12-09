#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Engine/render.h"
#include "Engine/contex.h"
#include "Engine/camera.h"
#include "Engine/data.h"
#include "Engine/mesh.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Contex* mainScreen;

protected:
    void resizeEvent(QResizeEvent * event);

};
#endif // MAINWINDOW_H
