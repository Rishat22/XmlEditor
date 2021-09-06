#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_MainLayout(new QVBoxLayout)
	, m_TreeView(new QTreeView)
	, m_WdgSearch(new WdgSearch)
{
	setObjectName("MainWindow");
	m_FilterDataModel.setSourceModel(m_TreeView->model());
	m_TreeView->setModel(&m_FilterDataModel);
	SetStyleSheet();
	m_MainLayout->addWidget(m_TreeView);
	m_MainLayout->addStretch();
	m_MainLayout->addWidget(m_WdgSearch);
	m_MainLayout->setStretch(0, 1); //Set Priorities to resize TreeView
	SetStyleSheet();

	auto mainWidget = new QWidget;
	mainWidget->setLayout(m_MainLayout);
	setCentralWidget(mainWidget);
	resize(1000, 600);
}

MainWindow::~MainWindow()
{
	delete m_TreeView;
}

void MainWindow::SetStyleSheet()
{
	m_TreeView->setStyleSheet('#' + m_TreeView->objectName() + "{background-color: rgb(128, 128, 128);}");

	QString styleObj = '#' + this->objectName() + "{background-color: rgb(128, 128, 128);}";
	setStyleSheet(styleObj);
}

void MainWindow::BtnSearchClicked(const QString& text)
{
	m_FilterDataModel.FilterData(text);
}
