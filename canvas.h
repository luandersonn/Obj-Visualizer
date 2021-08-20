#ifndef CANVAS_H
#define CANVAS_H
#include "GL/glew.h"
#include <QOpenGLWidget>
#include "utils.h"
#include "object3d.h"

class Canvas  : public QOpenGLWidget
{
    Q_OBJECT
public:
    Canvas(QWidget *parent);
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void openFile(std::string path);

private:
    std::vector<Object3D> objects;
    uint32_t vboIdCount;
};

#endif // CANVAS_H
