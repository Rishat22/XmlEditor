#include <QDir>
#include "Tools/Exceptions.h"
#include "TagsInfoLoader.h"

namespace Serialization
{

std::string TagsInfoDBFileName = "tags_info_db.xml";

TagsInfoLoader::TagsInfoLoader()
	: CXmlHandler()
	, m_LoadedFileName(std::string())
	, m_CurrSettingTagInfo(nullptr)
	, m_IsSettingsFound(false)
{
}

void TagsInfoLoader::Load(const std::string& strFileName)
{
	m_SettingTagsInfo.clear();
	m_LoadedFileName = strFileName;
	m_IsSettingsFound = false;
	CXmlHandler::Load(QDir::currentPath().toStdString() + '/' + TagsInfoDBFileName);
}


bool TagsInfoLoader::XmlNodeBegin(void)
{
	/* ToDo need to check right ending and right continue */
	auto topNodeIndex = 1;
	if(m_vStrOfNodes[topNodeIndex] == m_LoadedFileName)
	{
		m_IsSettingsFound = true;
		if(m_vStrOfNodes[topNodeIndex + 1] == "Tag" && m_vStrOfNodes[topNodeIndex + 2].empty())
		{
			m_SettingTagsInfo.emplace_back();
			m_CurrSettingTagInfo = &m_SettingTagsInfo.back();
		}
	}
	else if(!m_vStrOfNodes[topNodeIndex].empty())
		m_CurrSettingTagInfo = nullptr;

	return true;
}

bool TagsInfoLoader::XmlNodeDecode(const std::string& strNodeValue)
{
	if(!m_CurrSettingTagInfo)
	{
		return false;
	}

	try
	{
		std::string currTagName;
		if(GetCurrentTag(currTagName))
		{
			m_CurrSettingTagInfo->SetData(currTagName, strNodeValue);
		}
	}
	catch (const Tools::LoadSettingsException& exception)
	{
		std::cout << "Error loading tag information." << std::endl;
		std::cout << "Value = " << strNodeValue.data() << std::endl;
		exception.what();
		return false;
	}
	catch (const Tools::TypeException& exception)
	{
		exception.what();
		return false;
	}

	return true;
}

bool TagsInfoLoader::GetCurrentTag(std::string& tagName)
{
	auto emptyIt = std::find(m_vStrOfNodes.begin(), m_vStrOfNodes.end(), std::string());
	emptyIt--; //Last not empty
	tagName = *emptyIt;
	return emptyIt >= m_vStrOfNodes.begin() && emptyIt != m_vStrOfNodes.end();
}

bool TagsInfoLoader::IsSettingsInfoFound() const
{
	return m_IsSettingsFound;
}

bool TagsInfoLoader::FindTagInfo(const std::string& tagName, SettingTagInfo& tagInfo)
{
	auto tagInfoIt = std::find_if(m_SettingTagsInfo.begin(), m_SettingTagsInfo.end(),
	[&tagName](const SettingTagInfo& currTagInfo)
	{
		return currTagInfo.Name() == tagName;
	});

	if(tagInfoIt != m_SettingTagsInfo.end())
	{
		tagInfo = *tagInfoIt;
		return true;
	}
	return false;
}

}
