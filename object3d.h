#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <GL/glew.h>
#include <vector>
#include <array>
#include <string>

struct Vertex {
    float x;
    float y;
    float z;
};

struct Face {
    int index1;
    int index2;
    int index3;
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
private:

};

#endif // OBJECT3D_H
