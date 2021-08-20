#include "canvas.h"

#include <string>
#include <QOpenGLBuffer>



#define null NULL

Canvas::Canvas(QWidget *parent) : QOpenGLWidget(parent)
{
    vboIdCount = 0;
    objects = std::vector<Object3D>();
}

void Canvas::initializeGL()
{
    glClearColor(1,1,1,1);
}

void Canvas::paintGL()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    for(Object3D object : objects)
    {
        for(auto face : object.faces)
        {
            glVertex3fv(object.vertices[face[0]].data());
            glVertex3fv(object.vertices[face[1]].data());
            glVertex3fv(object.vertices[face[2]].data());
        }
    }
    glEnd();
    glFlush();
}

void Canvas::openFile(std::string path)
{
    auto object = Object3D(++this->vboIdCount, path);
    this->objects.push_back(object);
    this->repaint();
    // Creating the VBO
    /*
    glGenBuffers(1, &_3dObject.vboId);
    glBindBuffer(GL_ARRAY_BUFFER, _3dObject.vboId);
    float buffer [_3dObject.vertices.size()];

    for(int i = 0; i < _3dObject.vertices.size(); i++)
        buffer[i] = _3dObject.vertices. [i];
    glBufferData(GL_ARRAY_BUFFER, sizeof(3dObject.vertices), _3dObject.vertices.to, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);*/
}

void Canvas::resizeGL(int width, int height)
{    
    glLoadIdentity();
    float largura = 20.0;
    float altura = largura * height / width;
    glOrtho(-largura / 2.0f, largura / 2.0f, -altura / 2.0f, altura / 2.0f, -largura, largura);

}
