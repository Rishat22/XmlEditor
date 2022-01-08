#ifndef LISTITEMDELEGATE_H
#define LISTITEMDELEGATE_H
#include <QItemDelegate>

class ListItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ListItemDelegate(QObject *parent = nullptr);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
signals:
public slots:
private:

};

#endif // LISTITEMDELEGATE_H
