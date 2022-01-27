#include "SettingsModel.h"

SettingsModel::SettingsModel(QObject *parent)
	: QAbstractItemModel(parent)
	, m_SettingsLoader(*this)
{
	// The table consists of columns TagName, Type, Value
	std::copy(modelPropertyNames.begin(), modelPropertyNames.begin() + SettingsColumnsType::Description, std::back_inserter(m_NameColumns));
	// Creating instance of virtual root item
	m_RootItem = new QObject(this);
}

SettingsModel::~SettingsModel()
{
	delete m_RootItem;
}

void SettingsModel::addItem(QObject *item, const QModelIndex &parentIdx)
{
	beginInsertRows(parentIdx, rowCount(parentIdx), rowCount(parentIdx));
	item->setParent(objByIndex(parentIdx));
	endInsertRows();
}

void SettingsModel::updateItem(QObject* item, const SettingTagInfo& tagInfo)
{
	auto tagValue = tagInfo.GetData();
	item->setProperty(modelPropertyNames.at(SettingsColumnsType::Type).toUtf8(), tagValue.typeName());
	item->setProperty(modelPropertyNames.at(SettingsColumnsType::Value).toUtf8(), tagValue);
	item->setProperty(modelPropertyNames.at(SettingsColumnsType::Description).toUtf8(), tagInfo.GetDescription().data());
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

int SettingsModel::columnCount(const QModelIndex& /*parent*/) const
{
	return m_NameColumns.count();
}

void SettingsModel::clear()
{
	beginResetModel();
	delete m_RootItem;
	m_RootItem = new QObject(this);
	endResetModel();
}


Qt::ItemFlags SettingsModel::flags(const QModelIndex &index) const
{
	if(!index.isValid())
	{
		return Qt::NoItemFlags;
	}
	auto itemFlags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	if(static_cast<SettingsColumnsType>(index.column()) == SettingsColumnsType::Value
			&& objByIndex(index)->property(m_NameColumns.at(SettingsColumnsType::Value).toUtf8()).isValid())
		return itemFlags | Qt::ItemIsEditable;

	return itemFlags;
}

QVariant SettingsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
	{
		return m_NameColumns.at(section);
	}
	return QVariant();
}

QVariant SettingsModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	//Cell values retrieved from QObject properties
	switch (role) {
		case Qt::DisplayRole:
		{
			const auto& value = objByIndex(index)->property(modelPropertyNames.at(index.column()).toUtf8());
			if(index.column() == SettingsColumnsType::Value && value.type() == QVariant::StringList)
			{
				return (value.toStringList().empty()) ? QString() : value.toStringList().first();
			}
			return value;
		}
		case Qt::EditRole:
		{
			return objByIndex(index)->property(modelPropertyNames.at(index.column()).toUtf8());
		}
		case Qt::UserRole:
		case Qt::ToolTipRole:
		{
			return objByIndex(index)->property(modelPropertyNames.at(SettingsColumnsType::Description).toUtf8());
		}
		case Qt::TextAlignmentRole:
			return (index.column() == SettingsColumnsType::TagName) ? Qt::AlignLeft : Qt::AlignCenter;
		default:
			return QVariant();
	}
	return QVariant();
}

bool SettingsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(role != Qt::EditRole)
		return false;

	return objByIndex(index)->setProperty(modelPropertyNames.at(index.column()).toUtf8(), value);
}

void SettingsModel::loadSettings(const std::string& strFileName)
{
	clear();
	m_SettingsLoader.Load(strFileName);
}

void SettingsModel::saveSettings(const std::string& strFileName)
{
	m_SettingsLoader.Save(strFileName);
}
