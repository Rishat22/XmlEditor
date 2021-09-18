#ifndef TYPEEXCEPTION_H
#define TYPEEXCEPTION_H
#include "StableDeclaration.h"
#include <exception>

namespace Tools
{
struct TypeException : public std::exception
{
    virtual const char* what () const throw ()
    {
		return "Bad type conversion. \n";
    }
};

struct ColorException : TypeException
{
    const char* what () const throw () override
    {
        return "Incorrect text color option \n \
				Example string: 128,128,128,255 \n";
    }
};

struct SplitStringException : TypeException
{
     const char* what () const throw ()  override
    {
		return "Couldn't split the string. The separator may be incorrectly specified. \n";
    }
};

}
#endif // TYPEEXCEPTION_H
