#include "SettingsModel.h"

SettingsModel::SettingsModel(QObject *parent)
  : QAbstractItemModel(parent)
{
  //Creating instance of virtual root item
  m_RootItem = new QObject(this);
}

void SettingsModel::setColumns(const QStringList& columns)
{
  m_Columns = columns;
}

void SettingsModel::addItem(QObject *item, const QModelIndex &parentIdx)
{
  beginInsertRows(parentIdx, rowCount(parentIdx), rowCount(parentIdx));
  item->setParent(objByIndex(parentIdx));
  endInsertRows();
}

QObject *SettingsModel::objByIndex(const QModelIndex &index) const
{
  if (!index.isValid())
	return m_RootItem;
  return static_cast<QObject*>(index.internalPointer());
}

QModelIndex SettingsModel::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent))
	return QModelIndex();
  QObject* parentObj = objByIndex(parent);
  return createIndex(row, column, parentObj->children().at(row));
}

QModelIndex SettingsModel::parent(const QModelIndex &child) const
{
  QObject* childObj = objByIndex(child);
  QObject* parentObj = childObj->parent();
  //Virtual root item has invalid index (QModelIndex())
  if (parentObj == m_RootItem)
	return QModelIndex();
  //Grand parent item is used to get row coordinate for parent item
  QObject* grandParentObj = parentObj->parent();
  int row = grandParentObj->children().indexOf(parentObj);
  //First row cell is used as parent index
  return createIndex(row, 0, parentObj);
}

int SettingsModel::rowCount(const QModelIndex &parent) const
{
  return objByIndex(parent)->children().count();
}

int SettingsModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return m_Columns.count();
}

QVariant SettingsModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
	return QVariant();
  //Cell values retrieved from QObject properties
  if (role == Qt::DisplayRole) {
	return objByIndex(index)->property(m_Columns.at(index.column()).toUtf8());
  }
  return QVariant();
}
