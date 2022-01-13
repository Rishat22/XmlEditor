#include "SettingsTreeView.h"

SettingsTreeView::SettingsTreeView(QWidget* parent)
	: QTreeView(parent)
{
	connect(this, &QTreeView::clicked, this, &SettingsTreeView::objectClicked);
}

void SettingsTreeView::objectClicked(const QModelIndex& index)
{
	auto value = index.model()->data(index, Qt::UserRole);
	if(value.isValid())
	{
		emit showDescription(value.toString());
	}
}

