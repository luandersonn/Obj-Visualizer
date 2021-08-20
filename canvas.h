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
    void rotate(float degree, float x, float y, float z);
    void scale(float value);
    void translate(float x, float y, float z);
private:
    std::vector<Object3D> objects;
    uint32_t vboIdCount;
};

#endif // CANVAS_H
