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
                            geom.width() - 200,
                            geom.height() - 20);

    qApp->installEventFilter(this);

    // fill with color
    mainScreen->FillScreen(QColor(40,40,40));

    //=========================================================
    // GUI
    menuGrid = new QGridLayout();
    menuGrid->setSpacing(2);

    deleteBtn = new QPushButton();
    deleteBtn->setText("DeleteMesh");

    moveBtn = new QRadioButton();
    moveBtn->setText("Move mesh");
    rotateBtn = new QRadioButton();
    rotateBtn->setText("Rotate mesh");
    scaleBtn = new QRadioButton();
    scaleBtn->setText("Scale mesh");
    moveCamBtn = new QRadioButton();
    moveCamBtn->setText("Move camera");

    info = new QLabel();
    info->setText("Meshes: ");

    menuBox = new QGroupBox(this);
    menuBox->setGeometry( geom.width() - 200, 20, 180, geom.height() - 20);
    menuBox->setLayout(menuGrid);

    meshList = new QListWidget(menuBox);
    meshList->setGeometry( 10, 5, 280, 100);

    menuGrid->addWidget(info);
    menuGrid->addWidget(meshList);
    menuGrid->addWidget(deleteBtn);

    menuGrid->addWidget(moveBtn);
    menuGrid->addWidget(rotateBtn);
    menuGrid->addWidget(scaleBtn);
    menuGrid->addWidget(moveCamBtn);

    menuBox->show();
    //=========================================================

    // 30-40 fps
    renderTimer = new QTimer();
    renderTimer->setInterval(10);

    // connect open file button
    bool ok = true;
    ok &= (bool) QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::OpenFile);
    ok &= (bool) QObject::connect(this, &MainWindow::OpenFileSignal, mainScreen, &Contex::OnOpenFile);
    ok &= (bool) QObject::connect(renderTimer, &QTimer::timeout, mainScreen, &Contex::RenderLoop);
    ok &= (bool) QObject::connect(mainScreen, &Contex::AddMesh, this, &MainWindow::MainWindow::AddToList);
    ok &= (bool) QObject::connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::OnDeleteMesh);

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
    menuBox->setGeometry( event->size().width() - 200, 20, 180, event->size().height() - 20);
}

void MainWindow::OpenFile(){
    QString filePath = "";
    filePath = QFileDialog::getOpenFileName(this,
             tr("Open OBJ file"), "C:\\Users\\teoru\\_projects\\.MY_PRJ\\EvilGine\\.TestOBJ\\", tr("OBJ Files (*.obj)"));
    if(filePath != "")
        emit OpenFileSignal(filePath);
}

void MainWindow::AddToList(Mesh& mesh){
    meshList->addItem(mesh.GetName());
}

void MainWindow::OnDeleteMesh(){
    auto items = meshList->selectedItems();

    for(auto it = items.begin(); it != items.end(); ++it){
        auto itemName = (*it)->text();
        mainScreen->GetRender().DeleteMesh(itemName);
        meshList->takeItem(meshList->row(*it));
    }
}

double oldPosX;
double oldPosY;

void MainWindow::mouseMoveEvent(QMouseEvent *e){
    double rotateFactor = 0.1;

    oldPosX = this->size().width() / 2;
    oldPosY = this->size().height() / 2;

    if(moveCamBtn->isChecked()){
        // click event
        if(e->buttons() == Qt::LeftButton){
            rightClickMouse = true;
        }
        else
            rightClickMouse = false;

        // move event
        if (e->type() == QEvent::MouseMove && rightClickMouse){
            double x = e->pos().x();
            double y = e->pos().y();

            vec2 rotateVector = vec2(oldPosX - x, oldPosY - y);
            qDebug() << "x: " << rotateVector.GetX() << " y: " << rotateVector.GetY();

            oldPosX = rotateVector.GetX();
            oldPosY = rotateVector.GetY();

            // mainScreen->GetCamera().SetDirection(dir);

            double xRot = rotateVector.GetX() > 0 ? rotateFactor : -rotateFactor;
            double yRot = rotateVector.GetY() > 0 ? rotateFactor : -rotateFactor;

            auto camPos = mainScreen->GetCamera().GetPosition();

            for(auto it = mainScreen->GetRender().GetMeshes().begin(); it != mainScreen->GetRender().GetMeshes().end(); ++it){
                it->Rotate(X,xRot, camPos);
                it->Rotate(Y,yRot, camPos);
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    double moveFactor = 0.4;
    bool rotateFlag = false;
    ROT type = X;
    vec3 pos;

    if(rotateBtn->isChecked()){
        if(event->text() == "x" || event->text() == "ч"){
            type = X;
            rotateFlag = true;
        }
        if(event->text() == "y" || event->text() == "н"){
            type = Y;
            rotateFlag = true;
        }
        if(event->text() == "z" || event->text() == "я"){
            type = Z;
            rotateFlag = true;
        }

        if(rotateFlag){
            auto items = meshList->selectedItems();

            for(auto it = items.begin(); it != items.end(); ++it){
                auto itemName = (*it)->text();
                mainScreen->GetRender().GetMeshByName(itemName).Rotate(type, 0.1);
            }
        }
    }
    if(moveBtn->isChecked() || moveCamBtn->isChecked()){
        if(event->text() == "w" || event->text() == "ц")
            pos.SetY(moveFactor);
        if(event->text() == "a" || event->text() == "ф")
            pos.SetX(-moveFactor);
        if(event->text() == "s" || event->text() == "ы")
            pos.SetY(-moveFactor);
        if(event->text() == "d" || event->text() == "в")
            pos.SetX(moveFactor);
        if(event->text() == "q" || event->text() == "й")
            pos.SetZ(-moveFactor);
        if(event->text() == "e" || event->text() == "у")
            pos.SetZ(moveFactor);

        if(!moveCamBtn->isChecked()){
            auto items = meshList->selectedItems();

            for(auto it = items.begin(); it != items.end(); ++it){
                auto itemName = (*it)->text();
                mainScreen->GetRender().GetMeshByName(itemName).Move(pos);
            }
        }else{
            auto newPos = mainScreen->GetCamera().GetPosition() + pos;
            mainScreen->GetCamera().SetPosition(newPos);
        }
    }

    if(scaleBtn->isChecked()){
        vec3 scale = vec3(1.2,1.2,1.2);

        if(event->text() == "w" || event->text() == "ц")
            scale = vec3(1.2,1.2,1.2);

        if(event->text() == "s" || event->text() == "ы")
            scale = vec3(0.9,0.9,0.9);

        auto items = meshList->selectedItems();

        for(auto it = items.begin(); it != items.end(); ++it){
            auto itemName = (*it)->text();
            mainScreen->GetRender().GetMeshByName(itemName).Scale(scale);
        }
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){

  return false;
}
