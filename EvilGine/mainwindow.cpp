#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // create screen for drawing
    mainScreen = new Contex(this);

    // set geometry by mainwindow
    QRect geom = this->geometry();
    mainScreen->SetGeometry(geom.x(), geom.y(),
                            geom.size().width(),
                            geom.height());
    // fill with color
    mainScreen->FillScreen(QColor(40,40,40));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event){
    mainScreen->OnResize(event->size());
}
