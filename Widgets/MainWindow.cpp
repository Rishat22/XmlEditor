#include <QTreeView>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QDir>
#include "WdgSearch.h"
#include "MainWindow.h"
#include "GeneralItemsDelegate.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_MainLayout(new QVBoxLayout())
	, m_SettingsView(new SettingsTreeView(this))
	, m_TagDescriptionView(new QPlainTextEdit(this))
	, m_WdgSearch(new WdgSearch(this))
	, m_lasSelectedPath(QString())
{
	setObjectName("MainWindow");

	m_FilterDataModel.setSourceModel(&m_SourceModel);
	m_SettingsView->setModel(&m_FilterDataModel);
	m_MainLayout->addWidget(m_SettingsView);

	m_TagDescriptionView->setReadOnly(true);
	connect(m_SettingsView, &SettingsTreeView::showDescription, this, &MainWindow::SetDescriptionText);
	m_MainLayout->addWidget(m_TagDescriptionView);

	m_MainLayout->addStretch();
	connect(m_WdgSearch, &WdgSearch::TextSearch, this, &MainWindow::BtnSearchClicked);
	m_MainLayout->addWidget(m_WdgSearch);
	m_MainLayout->setStretch(0, 1); //Set Priorities to resize TreeView

	auto mainWidget = new QWidget;
	mainWidget->setLayout(m_MainLayout);
	setCentralWidget(mainWidget);

	SetStyleSheet();
	AddMenuBar();
	resize(1000, 600);
}

void MainWindow::AddMenuBar()
{
	auto menuBar = new QMenuBar(this);
	auto fileMenu = new QMenu(tr("File"));
	menuBar->addMenu(fileMenu);
	fileMenu->addActions(CreateFileActions());

	this->layout()->setMenuBar(menuBar);
}

QList<QAction*> MainWindow::CreateFileActions()
{
	QList<QAction*> fileActions;

	auto openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip(tr("Open an existing file"));
	connect(openAct, &QAction::triggered, this,
			[&]()
	{
		auto originalPath = QDir::homePath();
		if(!m_lasSelectedPath.isEmpty())
			originalPath = m_lasSelectedPath;
		QString filter = "XML files (*.xml)";
		QString fileName = QFileDialog::getOpenFileName(this, "Open file", originalPath, filter);
		m_lasSelectedPath = fileName;
		loadData(std::move(fileName.toStdString()));
	});
	fileActions.push_back(openAct);
	auto saveAct = new QAction(tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save the document to disk"));
	connect(saveAct, &QAction::triggered, this,
	[&]()
	{
		auto originalPath = QDir::homePath();
		if(!m_lasSelectedPath.isEmpty())
			originalPath = m_lasSelectedPath;
		QString filter = "XML files (*.xml)";
		QString fileName = QFileDialog::getSaveFileName(this, "Select the path to save", originalPath, filter);
		m_lasSelectedPath = fileName;
		saveData(std::move(fileName.toStdString()));
	});
	fileActions.push_back(saveAct);

	auto exitAct = new QAction(tr("Exit"), this);
	exitAct->setStatusTip(tr("Exit the application"));
	connect(exitAct, &QAction::triggered, this, &MainWindow::close);
	fileActions.push_back(exitAct);

	return fileActions;
}

void MainWindow::SetDescriptionText(const QString& descriptionText)
{
	m_TagDescriptionView->setPlainText(descriptionText);
}

void MainWindow::loadData(const std::string& strFileName)
{
	if(strFileName.empty())
		return;
	m_SourceModel.loadSettings(strFileName);
	m_SettingsView->expandAll();
	m_SettingsView->resizeColumnToContents(SettingsColumnsType::TagName);
	m_SettingsView->setItemDelegate(new GeneralItemsDelegate(m_SettingsView));
}

void MainWindow::saveData(const std::string& strFileName)
{
	if(strFileName.empty())
		return;
	m_SourceModel.saveSettings(strFileName);
}

MainWindow::~MainWindow()
{
	delete m_SettingsView;
}

void MainWindow::SetStyleSheet()
{
	m_SettingsView->setStyleSheet('#' + m_SettingsView->objectName() + "{background-color: rgb(128, 128, 128);}");

	QString styleObj = '#' + this->objectName() + "{background-color: rgb(128, 128, 128);}";
	setStyleSheet(styleObj);
}

void MainWindow::BtnSearchClicked(const QString& text)
{
	m_FilterDataModel.FilterData(text);
}
