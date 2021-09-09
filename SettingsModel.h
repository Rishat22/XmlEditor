#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H
#include <memory>
#include <QWidget>
#include <QAbstractItemModel>

class SettingsModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit SettingsModel(QObject *parent = nullptr);
    ~SettingsModel() = default;

    //Registers columns
    void setColumns(const QStringList& columns);
    //Adds child item from given parent item (parentIdx)
    void addItem(QObject* item, const QModelIndex &parentIdx);

    //Abstract virtual methods that needs to be implemented
    QVariant data(const QModelIndex &index, int role) const override;
//    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

protected:
    //Convenient method to retrieve item object from index
    QObject* objByIndex(const QModelIndex &index) const;
protected:
    QStringList m_Columns;
    //Virtual root item used to store the list of root content items
    QObject* m_RootItem;
};
#endif // SETTINGSMODEL_H
