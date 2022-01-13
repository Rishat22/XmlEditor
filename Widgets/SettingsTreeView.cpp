#include <QHeaderView>
#include <QScrollBar>
#include "SettingsTreeView.h"

SettingsTreeView::SettingsTreeView(QWidget* parent)
	: QTreeView(parent)
{
	connect(this, &QTreeView::clicked, this, &SettingsTreeView::objectClicked);
	SetStyleSheet();
}

void SettingsTreeView::objectClicked(const QModelIndex& index)
{
	auto value = index.model()->data(index, Qt::UserRole);
	if(value.isValid())
	{
		emit showDescription(value.toString());
	}
}

void SettingsTreeView::SetStyleSheet()
{
	/* ToDo temp hard-code style */
	setStyleSheet("QToolTip, QTableView, QListView, QTreeView, QGraphicsView{font-style: normal;font-size: 12pt;font-family: \"Liberation Mono\";}\
QToolTip, QTableView:enabled, QListView:enabled, QTreeView:enabled, QGraphicsView:enabled{padding: 3px;border: 1px solid rgba(255, 255, 255, 255);\
background: rgba(045, 045, 045, 255);alternate-background-color: rgba(070, 070, 070, 255);\
color: rgba(255, 255, 255, 255);selection-background-color: rgba(125, 125, 125, 255);\
gridline-color: rgba(255, 255, 255, 255);}");
	this->header()->setStyleSheet("QHeaderView{font-style: normal;\
font-size: 12pt;font-family: \"Liberation Mono\";\
		padding: 0px;}\
QHeaderView::section{background-color: rgba(070, 070, 070, 255);\
				 color: rgba(255, 255, 255, 255);\
				 padding: 2px;border: 1px solid rgba(255, 255, 255, 255);}\
QHeaderView::section:checked{background-color: rgba(070, 070, 070, 255);}\
QHeaderView::down-arrow{border: 1px solid rgba(255, 255, 255, 255);\
					background: rgba(070, 070, 070, 255);width: 3px;height: 3px;}\
QHeaderView::up-arrow{border: 1px solid rgba(255, 255, 255, 255);\
				  background: rgba(070, 070, 070, 255);width: 3px;height: 3px;}");
	this->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{border: 1px solid rgba(255, 255, 255, 255);\
background: rgba(065, 065, 065, 255);width: 15px;margin: 22px 0 22px 0;}\
QScrollBar::handle:vertical{background: rgba(070, 070, 070, 255);min-height: 10px;}\
QScrollBar::add-line:vertical{border: 1px solid rgba(255, 255, 255, 255);background: rgba(065, 065, 065, 255);\
height: 20px;subcontrol-position: bottom;subcontrol-origin: margin;}\
QScrollBar::sub-line:vertical{border: 1px solid rgba(255, 255, 255, 255);\
background: rgba(065, 065, 065, 255);height: 20px;subcontrol-position: top;subcontrol-origin: margin;}QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical{border: 1px solid rgba(255, 255, 255, 255);background: rgba(065, 065, 065, 255);width: 3px;height: 3px;}\
QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{background: none;}");

}

