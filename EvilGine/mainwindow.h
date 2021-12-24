#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QRadioButton>
#include <QPushButton>
#include <QFileDialog>
#include <QMainWindow>
#include <QListWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QLayout>
#include <QTimer>

#include "Engine/render.h"
#include "Engine/contex.h"
#include "Engine/camera.h"
#include "Engine/data.h"
#include "Engine/mesh.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void OpenFileSignal(const QString);

public slots:
    void OpenFile();
    void AddToList(Mesh& mesh);
    void OnDeleteMesh();

private:
    Ui::MainWindow *ui;
    Contex* mainScreen;
    QTimer *renderTimer;

    bool rightClickMouse;

    // GUI
    QGroupBox* menuBox;
    QListWidget* meshList;
    QGridLayout* menuGrid;
    QPushButton* deleteBtn;

    QRadioButton* moveBtn;
    QRadioButton* rotateBtn;
    QRadioButton* scaleBtn;
    QRadioButton* moveCamBtn;

    QLabel* info;

protected:
    void mouseMoveEvent(QMouseEvent *e);
    bool eventFilter(QObject *obj, QEvent *event);
    void resizeEvent(QResizeEvent * event);
    void keyPressEvent(QKeyEvent* event);

};
#endif // MAINWINDOW_H
