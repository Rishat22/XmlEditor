#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H
#include <QWidget>
#include <QAbstractItemModel>
#include "Serialization/SettingsLoader.h"

using namespace Serialization;

/* ToDo It can put all the functionality with columns in a separate class */
const QStringList modelPropertyNames{"TagName", "Type", "Value", "Description"};
enum SettingsColumnsType
{
	Begin = 0,
	TagName = Begin,
	Type,
	Value,
	Description
};

class SettingsModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit SettingsModel(QObject *parent = nullptr);
	~SettingsModel();

    //Adds child item from given parent item (parentIdx)
    void addItem(QObject* item, const QModelIndex &parentIdx);
    void updateItem(QObject* item, const SettingTagInfo& tagInfo);

    //Abstract virtual methods that needs to be implemented
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	void clear();
    /* Settings Loading */
    void loadSettings(const std::string& strFileName);
    void saveSettings(const std::string& strFileName);
signals:
    void setCustomEditingView(const QModelIndex& index, const QVariant::Type type);
protected:
    //Convenient method to retrieve item object from index
    QObject* objByIndex(const QModelIndex &index) const;
protected:
    QStringList m_NameColumns;
    //Virtual root item used to store the list of root content items
    QObject* m_RootItem;
    SettingsLoader m_SettingsLoader;
};
#endif // SETTINGSMODEL_H
