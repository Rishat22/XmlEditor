#ifndef SETTINGTAGINFO_H
#define SETTINGTAGINFO_H
#include <QString>
#include <QVariant>
namespace Serialization
{

class SettingTagInfo
{
public:
    SettingTagInfo() = default;
    SettingTagInfo(const std::string& tagName);
	std::string Name() const;
    QVariant GetData() const;
    std::string GetDescription() const;
	void SetData(const std::string& strTag, const std::string& strData);
	void SetData(const std::string& strData);
	std::string GetStrData(const QVariant& value);
private:
	void SetName(const std::string& strName);
    void SetType(const std::string& strType);
	void SetPossibleValues(const std::list<std::string>& PossibleValues);
    void SetDescription(const std::string& settingDescr);
private:
	std::string m_Name;
	QVariant::Type m_Type;
    QVariant m_Data;
	QStringList m_PossibleValues;
	std::string m_SettingDescription;
};

}

#endif // SETTINGTAGINFO_H
