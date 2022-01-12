#ifndef GENERALITEMSDELEGATE_H
#define GENERALITEMSDELEGATE_H
#include <QItemDelegate>

class GeneralItemsDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    GeneralItemsDelegate(QObject *parent = nullptr);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
signals:
public slots:
private:
    void setListModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // GENERALITEMSDELEGATE_H
