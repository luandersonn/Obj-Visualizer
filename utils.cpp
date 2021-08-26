#include "utils.h"
#include <time.h>

Utils::Utils()
{
    srand ( time ( NULL ) ); // Seed random number generator. Only do this once.
}


bool Utils::strStartWith(std::string original, std::string prefix)
{
    return original.rfind(prefix, 0) == 0;
}

std::vector<std::string> Utils::strSplit(std::string source, std::string delimiter)
{
    std::vector<std::string> array = std::vector<std::string>();
    size_t last = 0;
    size_t next = 0;
    while ((next = source.find(delimiter, last)) != std::string::npos)
    {
        array.push_back(source.substr(last, next-last));
        last = next + 1;
    }
    array.push_back(source.substr(last));
    return array;
}

float* Utils::get_random_color()
{
    auto color = new float[3];
    color[0] = (rand() % 255) / 255.0;
    color[1] = (rand() % 255) / 255.0;
    color[2] = (rand() % 255) / 255.0;
    return color;
}
