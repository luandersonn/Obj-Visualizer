#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(true)
    {
        auto fileName = QFileDialog::getOpenFileName(this,
                                                     tr("Open Image"),
                                                     "C:\\Users\\luand\\3D Objects",
                                                     tr("3D objects (*.obj)"));
        if(!fileName.isNull())
        {
            ui->myCanvas->openFile(fileName.toStdString());
        }
    }
    else
        ui->myCanvas->openFile("C:\\Users\\luand\\3D Objects\\Triangulo.obj");
}

