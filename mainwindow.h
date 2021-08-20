#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_translate_slider_x_valueChanged(int value);

    void on_translate_slider_y_valueChanged(int value);

    void on_translate_slider_z_valueChanged(int value);

    void on_scale_slider_valueChanged(int value);

    void on_rotate_slider_x_valueChanged(int value);

    void on_rotate_slider_y_valueChanged(int value);

    void on_rotate_slider_z_valueChanged(int value);

    void on_rotate_degree_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
