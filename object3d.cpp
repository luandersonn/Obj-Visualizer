#include "object3d.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <regex>

Object3D::Object3D(uint32_t vboId, string filePath)
{
    this->vboId = vboId;

    vertices = vector<array<float,3>>();
    faces = vector<array<int,3>>();

    ifstream MyReadFile(filePath);
    string line;
    while (getline (MyReadFile, line))
    {
        if(Utils::strStartWith(line, "v ")) // VERTEX
        {
            float vertex[3];
            auto count = 0;
            for(string pierce : Utils::strSplit(line, " "))
            {
                if(count == 0){
                    count++;
                    continue; // Pule o primeiro item, que é "v "
                }
                vertex[count - 1] = stof(pierce);
                count++;
            }

            vertices.push_back(array<float, 3> { vertex[0], vertex[1], vertex[2] });
        }
        else if(Utils::strStartWith(line, "f ")) // FACE
        {
            int face[3];
            auto count = 0;
            regex r(" \\d+"); // Get only numbers that start with space (' ') + backslash ('\')
            for(sregex_iterator i = sregex_iterator(line.begin(), line.end(), r); i != sregex_iterator(); ++i )
            {
                smatch m = *i;
                face[count] = stoi(m.str()) - 1; // File index start with 1 (!)
                count++;
            }
            faces.push_back(array<int, 3> { face[0], face[1], face[2] });
        }
    }
    MyReadFile.close();


}

// Lembre-se de destrutir as referencias
Object3D::~Object3D()
{

}
