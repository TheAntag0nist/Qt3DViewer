#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QTimer>

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

signals:
    void OpenFileSignal(const QString);

public slots:
    void OpenFile();

private:
    Ui::MainWindow *ui;
    Contex* mainScreen;
    QTimer *renderTimer;

protected:
    void resizeEvent(QResizeEvent * event);

};
#endif // MAINWINDOW_H
