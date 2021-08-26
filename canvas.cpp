#include "canvas.h"

#include <string>
#include <QOpenGLBuffer>
#include <QFile>
#include <QDebug>
#include <regex>

#define null NULL

Canvas::Canvas(QWidget *parent) : QOpenGLWidget(parent)
{    
    objects = std::vector<Object3D>();
}

void Canvas::initializeGL()
{
    // important!
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // Set the Viewport
    glViewport(0, 0, width(), height());

    openFile("C:\\Users\\luand\\3D Objects\\minecraft-steve.obj");
    //openFile("C:\\Users\\luand\\3D Objects\\Triangulo.obj");
    //openFile("C:\\Users\\luand\\3D Objects\\low-poly-fox-by-pixelmannen.obj");
    //Parse("C:\\Users\\luand\\3D Objects\\Triangulo.obj");
}


void Canvas::paintGL()
{
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    // render the triangle
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if(objects.size() == 0)
        return;
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    auto o = objects[0];
    auto elements = (sizeof(float) * o.vertices.size()) / sizeof(GLfloat);
    glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Canvas::openFile(std::string path)
{
    auto object = Object3D(path);
    this->objects.push_back(object);

    // Load shaders
    auto vertexShader = openShader(GL_VERTEX_SHADER, "D:\\luand\\Documents\\QT Projects\\glsl\\shade.txt");
    auto fragmentShader = openShader(GL_FRAGMENT_SHADER, "D:\\luand\\Documents\\QT Projects\\glsl\\fragment.txt");

    // Create program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /*
    float vertices [] {
        -0.5, 0.0, -0.5,
         0.5, 0.0, -0.5,
         0.5, 0.0,  0.5,
        -0.5, 0.0,  0.5,
         0.0, 0.5,  0.0};
    unsigned int indices []
    {
        0, 4, 1,
        1, 4, 2,
        0, 1, 4, // 4-1
        2, 4, 3,
        3, 4, 0
    };
    for(unsigned long long i = 0; i < object.vertices.size(); i += 3)
    {
        qDebug() << object.vertices[i]  << ",  " << object.vertices[i + 1] << ",  " << object.vertices[i + 2];
    }
    for(unsigned long long i = 0; i < object.faces.size(); i += 3)
    {
        //qDebug() << object.faces[i]  << ",  " << object.faces[i + 1] << ",  " << object.faces[i + 2];
    }
    /*float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };


    float * test = object.vertices.data();
    for(unsigned int i = 0; i < object.vertices.size(); i += 3)
    {
        qDebug() << test[i]  << ",  " << test[i + 1] << ",  " << test[i + 2];
    }
    qDebug() << sizeof(vertices) << sizeof(float) * object.vertices.size();*/


    //unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * object.vertices.size(), object.vertices.data(), GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * object.faces.size(), object.faces.data(), GL_STATIC_DRAW);
    // 4. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    this->repaint();
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

unsigned int Canvas::openShader(int type, string filePath)
{
    QFile file(filePath.c_str());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return NULL;

    QByteArray text = file.readAll();
    string str = text.toStdString();
    char * source = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), source);
    source[str.size()] = '\0';

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Error check
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        auto errorMessage = "ERROR::SHADER::COMPILATION_FAILED\n" + std::string(infoLog) + "\n";
        qDebug(errorMessage.c_str());
        exit(1);
    }
    delete [] source;
    return shader;
}

void Canvas::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}



void Canvas::Parse(string filePath)
{
    vertices = vector<float>();
    faces = vector<unsigned int>();
    auto file = QFile(filePath.data());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error("file read error");

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        processLine(line);
    }
}

void Canvas::processLine(QByteArray line)
{
    if(line.startsWith(QByteArray("v ")))
    {
        auto numberArray = Utils::strSplit(line.toStdString(), " ");
        vertices.push_back(stof(numberArray[1]));
        vertices.push_back(stof(numberArray[2]));
        vertices.push_back(stof(numberArray[3]));
    }
    else if(line.startsWith(QByteArray("f ")))
    {

        string s1 = line.toStdString();
        const regex e(R"( \d+)");

        std::sregex_iterator iter(s1.begin(), s1.end(), e);
        std::sregex_iterator end;

        int count = 0;
        while(iter != end)
        {
            for(unsigned i = 0; i < iter->size(); ++i)
            {
                if(count++ == 3)
                    break;
                auto value = (*iter)[i];
                auto valueStr = value.str();
                auto valueUInt = stoul(valueStr);
                valueUInt--;
                faces.push_back(valueUInt);

            }
            ++iter;
        }
    }
}
