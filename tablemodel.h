//#ifndef TABLEMODEL_H
//#define TABLEMODEL_H

//#include <QWidget>
//#include <QAbstractTableModel>
//#include <QVector>
//#include "entity.h"
//class TableModel : public QAbstractTableModel
//{
//    Q_OBJECT
//public:

//	explicit TableModel(QObject *parent = nullptr);
//	~TableModel();
//    // return кол-во элементов
//    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

//    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
//    // return параметры редактируемости элемента
//    Qt::ItemFlags flags(const QModelIndex &index) const override;
//    // сохраняет значение элемента
//    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
//    bool insertRows(int row, int count, const QModelIndex &parent) override;
//    bool removeRows(int row, int count, const QModelIndex &parent) override;
//    // return выбранный элемент
//	QVariant data(const QModelIndex &index, int role) const override;
//signals:

//public slots:

//private:
//    QVector<QStringList> parametersList_;
//    QStringList header_;
//	Entity* entity_;

//private:
//};
////Q_DECLARE_METATYPE(QList<Country*>)
//#endif // TABLEMODEL_H
