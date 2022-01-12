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
	switch (m_Type)
	{
		case QVariant::StringList :
		{
			auto newListData = m_Data.toStringList();
			auto firstElement = newListData.begin();
			auto curElement = std::find(newListData.begin(), newListData.end(), strData.data());
			std::swap(*firstElement, *curElement);
			m_Data = newListData;
			break;
		}
		case QVariant::Color :
		{
			std::string strR, strG, strB, strA;
			size_t t1, t2, t3;
			t1 =  strData.find(" ", 0); /* First space */
			t2 =  strData.find(" ", t1 + 1); /* Second space */
			t3 =  strData.find(" ", t2 + 1); /* Third space */

			strR =  strData.substr(0, t1);
			strG =  strData.substr(t1 + 1, t2 - t1 -1);
			strB =  strData.substr(t2 + 1, t3 - t2 -1);
			strA =  strData.substr(t3 + 1,  strData.length() - t3 - 1);

			m_Data = QColor(static_cast<int>(atoi(strR.data())), static_cast<int>(atoi(strG.data())),
							static_cast<int>(atoi(strB.data())), static_cast<int>(atoi(strA.data())));
			return;
		}
		default:
		{
			QVariant newData(QString::fromStdString(strData));
			newData.convert(m_Type);
			m_Data = newData;
			break;
		}
	}
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
