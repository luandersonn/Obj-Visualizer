#include "utils.h"

Utils::Utils()
{

}


bool Utils::strStartWith(std::string original, std::string prefix)
{
    return original.rfind(prefix, 0) == 0;
}

std::list<std::string> Utils::strSplit(std::string source, std::string delimiter)
{
    std::list<std::string> array = std::list<std::string>();
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
