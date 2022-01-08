#ifndef LOADSETTINGSEXCEPTION_H
#define LOADSETTINGSEXCEPTION_H
#include <exception>
#include <sstream>
#include <QStringList>
#include "StableDeclaration.h"

namespace Tools
{
/* ToDo Add exceptions for all other types */
struct LoadSettingsException : public std::exception
{
    virtual const char* what () const throw ()
    {
		return "Some proble with loading settings. \n";
    }
};

struct FileNotFoundException : LoadSettingsException
{
	FileNotFoundException(const std::string& fileName)
		: m_msg(std::string("The settings file was not found: "
							+ fileName + '\n'))
	{
	}

	virtual const char* what () const throw ()
	{
		return m_msg.c_str();
	}
private:
	std::string m_msg;
};

struct UnknownSettingsException : LoadSettingsException
{
	virtual const char* what () const throw ()
	{
		return "An unknown type of settings is selected for editing. \n";
	}
};

struct IncorrectTagValueList  : LoadSettingsException
{
    IncorrectTagValueList()
    {
        std::stringstream ss;
        ss << "Incorrect tag value list \n";
        m_msg = ss.str();
    }
    IncorrectTagValueList(const QStringList& possibleArgs)
    {
        std::stringstream ss;
        ss << "Incorrect tag value list \n";
        ss << " Possible args: \n";
        ss << possibleArgs.join("\n").toStdString();
		ss << std::endl;
        m_msg = ss.str();
     }
    const char* what() const throw () override
    {
        return m_msg.c_str();
    }
private:
        std::string m_msg;
};

}
#endif // LOADSETTINGSEXCEPTION_H
