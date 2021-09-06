#include "TableModel.h"
//TableModel::TableModel(QObject *parent)
//    : QAbstractTableModel(parent)
//{
//    parametersList_ = entity_->parametersList();
//    header_ = entity_->getHeader();
//}

//TableModel::~TableModel()
//{
//    QVector<QVector<QString>> outPutData;
//    for(int row = 0; row < entity_->getCountObjects(); ++row)
//    {
//        outPutData.push_back(QVector<QString>());
//        for(int column = 0; column < header_.size(); ++column)
//            outPutData[row].push_back(entity_->getObject(row, column));
//	}
//    delete entity_;
//}

//int TableModel::rowCount(const QModelIndex &parent) const
//{
//    Q_UNUSED(parent)
//    return entity_->getCountObjects();
//}

//int TableModel::columnCount(const QModelIndex &parent) const
//{
//    Q_UNUSED(parent)
//	return header_.size();
//}

//QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
//{

//    if (role == Qt::DisplayRole)
//    {
//        if(orientation == Qt::Horizontal)
//        {
//            return header_.at(section);
//        }
//        else return QVariant();
////        else if(orientation == Qt::Vertical)
////        {
////            return section;
////        }
//    }
//    else return QVariant();
//}



//QVariant TableModel::data(const QModelIndex &index, int role) const
//{
//    if(!index.isValid())
//        return QVariant();
//    int row, column;
//    row = index.row();
//    column = index.column();
//    switch (role) {
//    case Qt::DisplayRole:
//        return entity_->getObject(row, column);
//	case Qt::EditRole:
//		return parametersList_[column];
//    case Qt::TextAlignmentRole:
//        return Qt::AlignCenter;
//    default:
//        return QVariant();
//    }
//	return QVariant();
//}

//Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
//{
//    if(!index.isValid())
//	{
//        return Qt::NoItemFlags;
//	}
//	if(index.column() == static_cast<int>(Entity::DispArguments::ParameterName))
//	{
//		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
//	}
//    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
//}

//bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if(role != Qt::EditRole)
//        return false;
////    bool isHave = false;
////    foreach (const QString& var, parametersList_[index.column()])
////      if ( var == value.toString() )
////          isHave = true;
////    if(!isHave)
////        parametersList_[index.column()].push_back(value.toString());

//    return entity_->setObject(index.row(), index.column(), value.toString());
//}

//bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
//{
//    Q_UNUSED(parent)
//    beginInsertRows(QModelIndex(), row, row);
//    for(int i = 0; i < count; ++i)
//        entity_->addNewObject();
//    endInsertRows();
//    return true;
//}

//bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
//{
//    Q_UNUSED(parent)
//    if(row > entity_->getCountObjects() || row < 0)
//        return false;
//    beginRemoveRows(QModelIndex(), row, row); // no parent, one row to remove
//    for(int i = 0; i < count; ++i)
//        entity_->removeObject(row+i);
//    endRemoveRows();

//    return true;
//}



