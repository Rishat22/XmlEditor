#ifndef SETTINGSLOADER_H
#define SETTINGSLOADER_H
#include <memory>
#include <Serialization/CXmlHandler.h>
#include "StableDeclaration.h"
#include "BaseSetting.h"
#include "TagsInfoLoader.h"

namespace Serialization
{

class SettingsLoader : public CXmlHandler
{

public:
	SettingsLoader(SettingsModel& model);
	virtual ~SettingsLoader() = default;
public:
	bool Save(const std::string& strFileName);
	std::list<std::shared_ptr<BaseSetting> > Load(const std::string& strFileName);

	bool XmlNodeBegin(void) override;
	bool XmlNodeDecode(const std::string& strNodeValue) override;

private:
	bool LoadTagsInfo(const std::string& strFileName);
	bool GetCurrentParentTag(std::string& tagName);
	bool GetCurrentTag(std::string& tagName);
	void Iterate(CXmlNode* parentNode, const QModelIndex& index, const QAbstractItemModel* model);
private:
	TagsInfoLoader m_TagsInfoLoader;
	std::list<std::shared_ptr<BaseSetting>> m_Settings;
	SettingsModel& m_SourceModel;
	std::map<std::string, QObject*> m_currTreeBranch;
	QObject* m_CurrentItem;
	QObject* m_ParentItem;
	QObject* m_RootItem;

};

}

#endif // SETTINGSLOADER_H
