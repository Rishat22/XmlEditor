#include <QColor>
#include "SettingTagInfo.h"
#include "Tools/MathFunc.h"

namespace Serialization
{

std::string TagName = "Name";
std::string TagType = "Type";
std::string TagValues = "Values";
std::string TagDescription = "Description";
std::map<std::string, QVariant> StrNotationOfTypesList
{
	std::make_pair("Bool", bool()),
	std::make_pair("Int", int()),
	std::make_pair("Double", double()),
	std::make_pair("String", QString()),
	std::make_pair("List", QStringList()),
	std::make_pair("Color", QColor()),
	std::make_pair("List", QStringList())
};

SettingTagInfo::SettingTagInfo(const std::string& tagName)
	: m_Name(tagName)
	, m_Data(QVariant())
	, m_SettingDescription(std::string())
{
}

std::string SettingTagInfo::GetDescription() const
{
	return m_SettingDescription;
}

void SettingTagInfo::SetDescription(const std::string& settingDescr)
{
	m_SettingDescription = settingDescr;
}

std::string SettingTagInfo::Name() const
{
	return m_Name;
}

void SettingTagInfo::SetName(const std::string& strName)
{
	m_Name = strName;
}

void SettingTagInfo::SetPossibleValues(const std::list<std::string>& PossibleValues)
{
	QStringList list;
	for(const auto& possibleValue : PossibleValues)
	{
		list.append(possibleValue.data());
	}
	m_Data = list;
}

QVariant SettingTagInfo::GetData() const
{
	return m_Data;
}

void SettingTagInfo::SetData(const std::string& strTag, const std::string& strData)
{
	if(strTag == TagName)
	{
		SetName(strData);
	}
	else if(strTag == TagType)
	{
		SetType(strData);
	}
	else if(strTag == TagValues)
	{
		SetPossibleValues(Tools::MathFunc::SplitString(strData, ','));
	}
	else if(strTag == TagDescription)
	{
		SetDescription(strData);
	}
}

void SettingTagInfo::SetData(const std::string& strData)
{
	if(m_Type == QVariant::StringList)
	{
		auto newListData = m_Data.toStringList();
		auto firstElement = newListData.begin();
		auto curElement = std::find(newListData.begin(), newListData.end(), strData.data());
		std::swap(*firstElement, *curElement);
		m_Data = newListData;
		return;
	}
	QVariant newData(QString::fromStdString(strData));
	newData.convert(m_Type);
	m_Data = newData;
}

void SettingTagInfo::SetType(const std::string& strType)
{
	const auto typeIt = StrNotationOfTypesList.find(strType);
	if(typeIt != StrNotationOfTypesList.end())
	{
		m_Data = typeIt->second;
		m_Type = m_Data.type();
	}
}

}
