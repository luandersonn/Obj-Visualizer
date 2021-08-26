#include "object3d.h"
#include <iostream>
#include <string.h>
#include <qdebug.h>
#include <regex>
#include <utils.h>



Object3D::Object3D(string filePath)
{    
    rotate = Vertex();
    translate = Vertex();
    scale = Vertex();
    scale.x = 1;
    scale.y = 1;
    scale.z = 1;

    Parse(filePath);
}

void Object3D::Parse(string filePath)
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

void Object3D::processLine(QByteArray line)
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
        unsigned int count = 0;
        while(iter != end)
        {
            for(unsigned i = 0; i < iter->size(); ++i)
            {
                if(count++ == 3)
                    break;
                faces.push_back(stoul(((*iter)[i]).str()) - 1);

            }
            ++iter;
        }
    }
}
