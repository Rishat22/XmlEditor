#include "WdgSearch.h"
#include <QAction>

WdgSearch::WdgSearch(QWidget *parent)
	: QWidget(parent)
	, m_SearchEdit(new QLineEdit)
	, m_SearchBtn(new QPushButton("Search", this))
	, m_MainLayout( new QHBoxLayout)
{
	setObjectName("WdgSearch");
	m_SearchBtn->setObjectName("SearchButton");
	m_MainLayout->addWidget(m_SearchEdit);
	m_MainLayout->addWidget(m_SearchBtn);
	m_MainLayout->addStretch();

	connect(m_SearchBtn, &QPushButton::clicked, this, &WdgSearch::MakeTextSearch);

	m_MainLayout->setContentsMargins(0, 0, 0, 0);
	SetStyleSheet();
	setLayout(m_MainLayout);

	auto findAct = new QAction(this);
	findAct->setShortcuts(QKeySequence::Find);
	connect(findAct, &QAction::triggered, this, &WdgSearch::SetLineEditFocus);
	this->addAction(findAct);

	connect(m_SearchEdit, &QLineEdit::returnPressed, m_SearchBtn, &QPushButton::click);

}

void WdgSearch::MakeTextSearch()
{
	emit TextSearch(m_SearchEdit->text());
}

void WdgSearch::SetLineEditFocus()
{
	m_SearchEdit->setFocus();
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
