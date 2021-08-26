#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <GL/glew.h>
#include <vector>
#include <array>
#include <string>
#include <qfile.h>


struct Vertex {
    float x = 0;
    float y = 0;
    float z = 0;
    float degree = 0;
};

using namespace std;

class Object3D
{
public:
    Object3D(std::string fileName);    
    uint32_t VBO;
    uint32_t EBO;
    uint32_t VAO;
    vector<float> vertices;
    vector<uint32_t> faces;
    Vertex scale;
    Vertex translate;
    Vertex rotate;

    void Parse(string filePath);
private:
    void processLine(QByteArray line);


};

#endif // OBJECT3D_H
