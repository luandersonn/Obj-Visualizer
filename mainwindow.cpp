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


void MainWindow::on_translate_slider_x_valueChanged(int value)
{
    ui->myCanvas->translate(ui->translate_slider_x->value() / 10.0,
                            ui->translate_slider_y->value() / 10.0,
                            ui->translate_slider_z->value() / 10.0);
}


void MainWindow::on_translate_slider_y_valueChanged(int value)
{
    ui->myCanvas->translate(ui->translate_slider_x->value() / 10.0,
                            ui->translate_slider_y->value() / 10.0,
                            ui->translate_slider_z->value() / 10.0);
}


void MainWindow::on_translate_slider_z_valueChanged(int value)
{
    ui->myCanvas->translate(ui->translate_slider_x->value() / 10.0,
                            ui->translate_slider_y->value() / 10.0,
                            ui->translate_slider_z->value() / 10.0);
}

void MainWindow::on_scale_slider_valueChanged(int value)
{
    ui->myCanvas->scale(ui->scale_slider->value() / 10.0);

}


void MainWindow::on_rotate_slider_x_valueChanged(int value)
{
    ui->myCanvas->rotate(ui->rotate_degree->value(),
                         ui->rotate_slider_x->value() / 10.0,
                         ui->rotate_slider_y->value() / 10.0,
                         ui->rotate_slider_z->value() / 10.0);
}


void MainWindow::on_rotate_slider_y_valueChanged(int value)
{
    ui->myCanvas->rotate(ui->rotate_degree->value(),
                         ui->rotate_slider_x->value() / 10.0,
                         ui->rotate_slider_y->value() / 10.0,
                         ui->rotate_slider_z->value() / 10.0);
}


void MainWindow::on_rotate_slider_z_valueChanged(int value)
{
    ui->myCanvas->rotate(ui->rotate_degree->value(),
                         ui->rotate_slider_x->value() / 10.0,
                         ui->rotate_slider_y->value() / 10.0,
                         ui->rotate_slider_z->value() / 10.0);
}


void MainWindow::on_rotate_degree_valueChanged(int arg1)
{
    ui->myCanvas->rotate(ui->rotate_degree->value(),
                         ui->rotate_slider_x->value() / 10.0,
                         ui->rotate_slider_y->value() / 10.0,
                         ui->rotate_slider_z->value() / 10.0);
}

