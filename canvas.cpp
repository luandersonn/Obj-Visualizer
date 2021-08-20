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
    glLoadIdentity();
    float largura = 50.0;
    float altura = largura * height() / width();
    glOrtho(-largura / 2.0f, largura / 2.0f, -altura / 2.0f, altura / 2.0f, -500, 500);

    for(Object3D object : objects)
    {
        glTranslatef(object.translate.x, object.translate.y, object.translate.z);
        glRotatef(object.rotate.degree, object.rotate.x, object.rotate.y, object.rotate.z);
        glScalef(object.scale.x, object.scale.y, object.scale.z);

        glBegin(GL_TRIANGLES);
        int index = 0;
        for(auto face : object.faces)
        {
            auto color = object.colors[index];
            glColor3fv(color.data());
            glVertex3fv(object.vertices[face[0]].data());
            glVertex3fv(object.vertices[face[1]].data());
            glVertex3fv(object.vertices[face[2]].data());
            index++;
        }
        glEnd();
    }
    glFlush();   
}

void Canvas::openFile(std::string path)
{
    auto object = Object3D(++this->vboIdCount, path);

    this->objects.push_back(object);
    this->repaint();
    // Creating the VBO
/*
    glGenBuffers(1, &object.vboId);
    glBindBuffer(GL_ARRAY_BUFFER, object.vboId);
    float buffer [object.vertices.size()];

    int index = 0;
    for(auto face : object.faces)
    {

    }
    for(int i = 0; i < _3dObject.vertices.size(); i++)
        buffer[i] = _3dObject.vertices. [i];
    glBufferData(GL_ARRAY_BUFFER, sizeof(3dObject.vertices), _3dObject.vertices.to, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);*/
}

void Canvas::rotate(float degree, float x, float y, float z)
{
    if(objects.size() > 0)
    {
        objects[0].rotate.degree = degree;
        objects[0].rotate.x = x;
        objects[0].rotate.y = y;
        objects[0].rotate.z = z;
        this->repaint();
    }
}

void Canvas::scale(float value)
{
    if(objects.size() > 0)
    {
        objects[0].scale.x = value;
        objects[0].scale.y = value;
        objects[0].scale.z = value;
        this->repaint();
    }
}

void Canvas::translate(float x, float y, float z)
{
    if(objects.size() > 0)
    {
        objects[0].translate.x = x;
        objects[0].translate.y = y;
        objects[0].translate.z = z;
        this->repaint();
    }
}

void Canvas::resizeGL(int width, int height)
{        
}
