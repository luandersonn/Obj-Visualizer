#ifndef UTILS_H
#define UTILS_H

#include "string"
#include "list"


class Utils
{
public:
    Utils();
    // Retorna true se uma string começa com um certo prefixo
    static bool strStartWith(std::string original, std::string prefix);
    // Função Split presentes na classe String do Java/C#
    static std::list<std::string> strSplit(std::string source, std::string delimiter);
};

#endif // UTILS_H