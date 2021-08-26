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
    uint32_t openShader(int type, std::string filePath);

    void Parse(string filePath);
    void processLine(QByteArray line);

private:
    vector<Object3D> objects;
    vector<float> vertices;
    vector<uint32_t> faces;
    uint32_t shaderProgram;    
    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;
};

#endif // CANVAS_H
