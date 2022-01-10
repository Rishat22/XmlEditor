#include "Tools/Exceptions.h"
#include "SettingsModel.h"
#include "SettingsLoader.h"

namespace Serialization
{

SettingsLoader::SettingsLoader(SettingsModel& model)
	: CXmlHandler()
	, m_SourceModel(model)
	, m_CurrentItem(nullptr)
	, m_ParentItem(nullptr)
	, m_RootItem(nullptr)
{
}

std::list<std::shared_ptr<BaseSetting>> SettingsLoader::Load(const std::string& strFileName)
{
	m_Settings.clear();
	if(LoadTagsInfo(strFileName))
	{
		CXmlHandler::Load(strFileName);
	}
	return m_Settings;
}

bool SettingsLoader::LoadTagsInfo(const std::string& strFileName)
{
	std::size_t LastSlashPos = strFileName.find_last_of("/");
	auto tagInfoFileName = strFileName.substr(LastSlashPos + 1);
	tagInfoFileName = tagInfoFileName.substr(0, tagInfoFileName.find_last_of("."));
	m_TagsInfoLoader.Load(tagInfoFileName);
	if(m_TagsInfoLoader.IsSettingsInfoFound())
	{
		return true;
	}
	else
	{
		std::cout << "Information about the current name of the setting was not found: " << tagInfoFileName << std::endl;
		return false;
	}
}

bool SettingsLoader::Save(const std::string& strFileName)
{
	/*CXmlNode* document = */NewDocument(strFileName);

//	CXmlNode* parentNode = NewNode("MainSettings", document);
//	BaseSetting base_setting;
//	CXmlNode* nameNode = NewNode(base_setting.GetTag("NameWidget"), parentNode);
//	auto strData = base_setting.GetData().toString();
//	nameNode->SetValue(strData);

	bool bRes = SaveDocument();

	return bRes;
}

bool SettingsLoader::XmlNodeBegin(void)
{
	std::string currTagName;
	if(GetCurrentTag(currTagName))
	{
		std::string parentTagName;
		if(GetCurrentParentTag(parentTagName))
		{
			auto parentBranchItem = m_currTreeBranch.find(parentTagName);
			if(parentBranchItem != m_currTreeBranch.end())
			{
				m_ParentItem = parentBranchItem->second;
			}
		}
		else
		{
			m_ParentItem = nullptr;
			m_RootItem = nullptr;
			m_currTreeBranch.clear();
		}

		QObject* newItem;
		if(m_RootItem == nullptr)
		{
			newItem = new QObject();
		}
		else
		{
			newItem = (m_ParentItem == nullptr) ? new QObject(m_RootItem) : new QObject(m_ParentItem);
		}

		newItem->setObjectName(currTagName.data());
		newItem->setProperty("TagName", currTagName.data());
		if(m_RootItem == nullptr)
		{
			m_ParentItem = newItem;
			m_RootItem = newItem;
			m_SourceModel.addItem(m_ParentItem, QModelIndex());
		}
		m_CurrentItem = newItem;
		m_currTreeBranch[currTagName] = newItem;
	}
	return true;
}

bool SettingsLoader::XmlNodeDecode(const std::string& strNodeValue)
{
	bool bRes = true;

	try
	{
		std::string currTagName;
		SettingTagInfo tagInfo;
		if(GetCurrentTag(currTagName) && m_TagsInfoLoader.FindTagInfo(currTagName, tagInfo))
		{
			tagInfo.SetData(strNodeValue);
			m_SourceModel.updateItem(m_CurrentItem, tagInfo);
		}
		else
			std::cout << "can not find tag: " << currTagName.data();
	}
	catch (const Tools::LoadSettingsException& exception)
	{
		std::cout << "Error loading Settings." << std::endl;
		std::cout << "Value = " << strNodeValue.data() << std::endl;
		exception.what();
	}
	catch (const Tools::TypeException& exception)
	{
		exception.what();
		bRes = false;
	}
	return bRes;
}

bool SettingsLoader::GetCurrentParentTag(std::string& tagName)
{
	auto emptyIt = std::find(m_vStrOfNodes.begin(), m_vStrOfNodes.end(), std::string());
	emptyIt--; //Last not empty
	emptyIt--; //Parent of this
	if(emptyIt >= m_vStrOfNodes.begin() && emptyIt != m_vStrOfNodes.end())
	{
		tagName = *emptyIt;
		return true;
	}
	return false;
}

bool SettingsLoader::GetCurrentTag(std::string& tagName)
{
	auto emptyIt = std::find(m_vStrOfNodes.begin(), m_vStrOfNodes.end(), std::string());
	emptyIt--; //Last not empty
	if(emptyIt >= m_vStrOfNodes.begin() && emptyIt != m_vStrOfNodes.end())
	{
		tagName = *emptyIt;
		return true;
	}
	return false;
}


}
