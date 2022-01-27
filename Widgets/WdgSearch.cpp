#include <QAction>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QString>
#include <QComboBox>
#include "WdgSearch.h"

WdgSearch::WdgSearch(QWidget *parent)
	: QFrame(parent, Qt::Dialog)
	, m_SearchType(new QComboBox(this))
	, m_SearchEdit(new QLineEdit(this))
	, m_SearchBtn(new QPushButton("Search", this))
{
	setObjectName("WdgSearch");
	m_SearchBtn->setObjectName("SearchButton");

	const auto m_MainLayout= new QVBoxLayout();
	const auto lineEditLayout= new QHBoxLayout();
	lineEditLayout->addWidget(m_SearchEdit);
	lineEditLayout->addWidget(m_SearchBtn);

	m_MainLayout->addWidget(m_SearchType);
	m_MainLayout->addLayout(lineEditLayout);
	connect(m_SearchBtn, &QPushButton::clicked, this, &WdgSearch::MakeTextSearch);
	connect(m_SearchEdit, &QLineEdit::returnPressed, m_SearchBtn, &QPushButton::click);

	SetStyleSheet();
	setLayout(m_MainLayout);

}

void WdgSearch::addFilterType(const QString& type)
{
	m_SearchType->addItem(type);
}

void WdgSearch::MakeTextSearch()
{
	emit SearchTextByType(m_SearchEdit->text(), m_SearchType->currentText());
}

void WdgSearch::showEvent(QShowEvent* event)
{
	m_SearchEdit->setFocus();
	QWidget::showEvent(event);
}

auto setColorButton = [](QPushButton* button, QString color){
	QString nameButton = '#' + button->objectName();
	button->setStyleSheet(nameButton + "{background-color:" + color +
						  "; color: #ffffff; border-width: 1px; border-style: solid; "
						   "border-color: rgb(181,181,181); "
						   "font-family: Arial;"
						   "padding: 2px;"
						   "font-size: 12pt; font-weight: 450; border-radius: 3;}"
						   + nameButton + ":pressed{"
						   "background-color: #ffffff;"
						   "color:" + color + ';' +
						   "border-width: 1px; "
						   "border-style: solid; "
						   "border-color: rgb(181,181,181); "
						   "font-family: Arial;"
						   "padding: 2px;"
						   "font-size: 12pt; font-weight: 450; border-radius: 3;}"
						   );
};


void WdgSearch::SetStyleSheet()
{
	QString nameObj = '#' + this->objectName();
	QString styleObj = nameObj + "{background-color: rgb(238, 238, 238);}";
	this->setStyleSheet(styleObj);
	setColorButton(m_SearchBtn, "#071406");
}
