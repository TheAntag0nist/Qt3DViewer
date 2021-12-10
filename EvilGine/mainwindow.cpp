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
    mainScreen->SetGeometry( 0, 20,
                            geom.width(),
                            geom.height() - 20);
    // fill with color
    mainScreen->FillScreen(QColor(40,40,40));

    // 30-40 fps
    renderTimer = new QTimer();
    renderTimer->setInterval(10);

    // connect open file button
    bool ok = true;
    ok &= (bool) QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::OpenFile);
    ok &= (bool) QObject::connect(this, &MainWindow::OpenFileSignal, mainScreen, &Contex::OnOpenFile);
    ok &= (bool) QObject::connect(renderTimer, &QTimer::timeout, mainScreen, &Contex::RenderLoop);

    if(!ok){
        qDebug() << "[ERR]:> MainWindow::connect(...);";
        this->close();
    }

    renderTimer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event){
    mainScreen->OnResize(event->size());
}

void MainWindow::OpenFile(){
    QString filePath = "";
    filePath = QFileDialog::getOpenFileName(this,
             tr("Open OBJ file"), "C:\\", tr("OBJ Files (*.obj)"));
    if(filePath != "")
        emit OpenFileSignal(filePath);
}
