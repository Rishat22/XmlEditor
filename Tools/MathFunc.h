#ifndef GUIFUNC_H
#define GUIFUNC_H
#include "StableDeclaration.h"

namespace Tools
{
class MathFunc
{
public:
    MathFunc() = default;
    static std::vector<std::string> SplitString(const std::string& strText , char delimiter);
    static QColor StringToColor(const std::string& strColor);
};

}
#endif // GUIFUNC_H
