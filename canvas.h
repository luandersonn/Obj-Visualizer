#ifndef CANVAS_H
#define CANVAS_H
#include "GL/glew.h"
#include <QOpenGLWidget>

class Canvas  : public QOpenGLWidget
{
    Q_OBJECT
public:
    Canvas(QWidget *parent);
    void initializeGL();
    void paintGL();
    void openFile(std::string path);
};

#endif // CANVAS_H
