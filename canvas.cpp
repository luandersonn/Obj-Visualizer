#include "canvas.h"
#include <iostream>
#include <fstream>
#include <string>
#include "QOpenGLBuffer"
#define null NULL

Canvas::Canvas(QWidget *parent) : QOpenGLWidget(parent)
{

}

void Canvas::initializeGL()
{
    glClearColor(1,1,1,1);
}

void Canvas::paintGL()
{   
    glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0);
        glVertex3f(-0.5, -0.5, 0.0);
        glColor3f(0, 1, 0);
        glVertex3f( 0.5, -0.5, 0.0);
        glColor3f(0, 0, 1);
        glVertex3f( 0.0,  0.5, 0.0);
    glEnd();
    glFlush();
}

#include <iostream>
#include <fstream>

void Canvas::openFile(std::string path)
{
    std::ifstream MyReadFile(path);

    std::string line;
    while (getline (MyReadFile, line))
    {

    }

    MyReadFile.close();
}
