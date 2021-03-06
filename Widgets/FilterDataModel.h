#ifndef FILTER_DATA_MODEL_H
#define FILTER_DATA_MODEL_H

#include <QObject>
#include <QSortFilterProxyModel>

class FilterDataModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit FilterDataModel(QObject *parent = nullptr);
    void FilterData(const QString& pattern);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

};

#endif // FILTER_DATA_MODEL_H
