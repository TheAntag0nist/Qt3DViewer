#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("EvilGine - v0.0.2v");
    // create screen for drawing
    mainScreen = new Contex(this);

    // set geometry by mainwindow
    QRect geom = this->geometry();
    mainScreen->SetGeometry( 0, 0,
                            geom.width(),
                            geom.height());
    // fill with color
    mainScreen->FillScreen(QColor(40,40,40));

    Mesh mesh;
    mesh.ReadOBJ("C:\\Users\\teoru\\_projects\\.MY_PRJ\\EvilGine\\.TestOBJ\\cube.obj");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event){
    mainScreen->OnResize(event->size());
}
