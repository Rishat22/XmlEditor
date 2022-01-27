#include "FilterDataModel.h"

FilterDataModel::FilterDataModel(QObject *parent)
	: QSortFilterProxyModel(parent)
{
}

void FilterDataModel::FilterData(const QString& pattern)
{
	setFilterRegExp(pattern);
}

bool FilterDataModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
	if(filterRegExp().isEmpty()==false)
	{
		// get source-model index for current row
		QModelIndex source_index = sourceModel()->index(source_row, filterKeyColumn(), source_parent);
		if(source_index.isValid())
		{
			// if any of children matches the filter, then current index matches the filter as well
			for(auto childRow = 0; childRow < sourceModel()->rowCount(source_index); ++childRow)
			{
				if(filterAcceptsRow(childRow, source_index))
				{
					return true ;
				}
			}
			// check current index itself :
			const QString& keyData = sourceModel()->data(source_index, filterRole()).toString();
			return keyData.contains(filterRegExp()) ;
		}
	}
	/* parent call for initial behaviour */
	return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent) ;
}




