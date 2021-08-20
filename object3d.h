#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <GL/glew.h>
#include <vector>
#include <array>
#include <string>

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
    Object3D(uint32_t vboId, std::string fileName);
    ~Object3D();
    uint32_t vboId;
    vector<array<float, 3>> vertices;
    vector<array<int, 3>> faces;
    vector<array<float, 3>> colors;
    Vertex scale;
    Vertex translate;
    Vertex rotate;
private:

};

#endif // OBJECT3D_H
