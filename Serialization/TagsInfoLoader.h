#ifndef TAGSINFOLOADER_H
#define TAGSINFOLOADER_H
#include <Serialization/CXmlHandler.h>
#include "SettingTagInfo.h"
#include "StableDeclaration.h"

namespace Serialization
{

class TagsInfoLoader : public CXmlHandler
{
public:
    TagsInfoLoader();
    virtual ~TagsInfoLoader() = default;
	void Load(const std::string& strFileName);
	bool IsSettingsInfoFound() const;
	bool FindTagInfo(const std::string& tagName, SettingTagInfo& tagInfo);
protected:
    bool XmlNodeBegin(void) override;
    bool XmlNodeDecode(const std::string& strNodeValue) override;
private:
	bool GetCurrentTag(std::string& tagName);
private:
    std::string m_LoadedFileName;
	std::vector<SettingTagInfo> m_SettingTagsInfo;
    SettingTagInfo* m_CurrSettingTagInfo;
	bool m_IsSettingsFound;
};

}

#endif // TAGSINFOLOADER_H
