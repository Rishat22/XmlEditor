#include <QTreeView>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QDir>
#include "COutputLogger.h"
#include "WdgSearch.h"
#include "GeneralItemsDelegate.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_SettingsView(new SettingsTreeView(this))
	, m_TagDescriptionView(new QPlainTextEdit(this))
	, m_LogsInfoView(new QPlainTextEdit(this))
	, m_WdgSearch(new WdgSearch())
	, m_lasSelectedPath(QString())
{
	setObjectName("MainWindow");

	m_FilterDataModel.setSourceModel(&m_SourceModel);
	m_SettingsView->setModel(&m_FilterDataModel);
	m_SettingsView->setItemDelegate(new GeneralItemsDelegate(m_SettingsView));

	auto topLayout = new QHBoxLayout();
	topLayout->addWidget(m_SettingsView);

	m_TagDescriptionView->setReadOnly(true);
	connect(m_SettingsView, &SettingsTreeView::showDescription, this, &MainWindow::SetDescriptionText);
	topLayout->addWidget(m_TagDescriptionView);
	topLayout->addStretch();

	for(const auto& propertyName : modelPropertyNames)
	{
		m_WdgSearch->addFilterType(propertyName);
	}
	connect(m_WdgSearch, &WdgSearch::SearchTextByType, this, &MainWindow::SearchTextByType);
	topLayout->setStretch(0, 5); //Set Priorities to resize TreeView
	topLayout->setStretch(1, 2); //Set Priorities to resize DescriptionView widget

	auto mainWidget = new QWidget;
	auto mainLayout = new QVBoxLayout();
	mainLayout->addLayout(topLayout);

	m_LogsInfoView->setReadOnly(true);

	mainLayout->addWidget(m_LogsInfoView);
	mainLayout->setStretch(0, 5); //Set Priorities to resize top layout
	mainLayout->setStretch(1, 2); //Set Priorities to resize logsInfo widget

	mainWidget->setLayout(mainLayout);
	setCentralWidget(mainWidget);

	SetStyleSheet();
	AddMenuBar();
	resize(1000, 600);

	auto& manager = COutputLoggerManager::GetInstance();
	manager.AddLogger(new CConsoleLogger());
	manager.AddLogger(new CPlainTextLogger(m_LogsInfoView));
	qInstallMessageHandler(customMessageHandler);
}

void MainWindow::customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	QString resultMsg;
	QRegExp rx("([\\w-]+::[\\w-]+)");
	if (rx.indexIn(context.function) == -1)
	{
		return;
	}
	QString function = rx.cap(1);
	QString msgSep = (msg.length() > 0) ? " >> " : "";

	switch (type) {
		case QtInfoMsg:
		{
			resultMsg = QString("Info: %1%2%3").arg(function).arg(msgSep).arg(msg);
			break;
		}
		case QtDebugMsg:
		{
			resultMsg = QString("Debug: %1%2%3").arg(function).arg(msgSep).arg(msg);
			break;
		}
		case QtWarningMsg:
		{
			resultMsg = QString("Warning: %1%2%3").arg(function).arg(msgSep).arg(msg);
			break;
		}
		case QtCriticalMsg:
		{
			resultMsg = QString("Critical: %1%2%3").arg(function).arg(msgSep).arg(msg);
			break;
		}
		case QtFatalMsg:
		{
			resultMsg = QString("Fatal: %1%2%3").arg(function).arg(msgSep).arg(msg);
			abort();
			break;
		}
	}
	auto& manager = COutputLoggerManager::GetInstance();

	manager.Print(type, resultMsg);
}

void MainWindow::AddMenuBar()
{
	auto menuBar = new QMenuBar(this);

	menuBar->addMenu(CreateFileMenu());
	menuBar->addMenu(CreateSearchMenu());

	this->layout()->setMenuBar(menuBar);
}

QMenu* MainWindow::CreateFileMenu()
{
	auto fileMenu = new QMenu(tr("File"));
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

	fileMenu->addActions(fileActions);
	return fileMenu;
}

QMenu* MainWindow::CreateSearchMenu()
{
	auto searchMenu = new QMenu(tr("Search"));
	auto searchAct = new QAction(tr("Search"), this);
	searchAct->setShortcuts(QKeySequence::Find);
	searchAct->setStatusTip(tr("Changing search parameters"));
	connect(searchAct, &QAction::triggered, this,
	[&]()
	{
		m_WdgSearch->show();
	});
	searchMenu->addAction(searchAct);
	return searchMenu;
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
	m_SettingsView->setColumnWidth(SettingsColumnsType::TagName, m_SettingsView->width() * .4);
	m_SettingsView->setColumnWidth(SettingsColumnsType::Type, m_SettingsView->width() * .2);
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
	QString styleObj = '#' + this->objectName() + "{background-color: rgb(128, 128, 128);}";
	setStyleSheet(styleObj);
	/* ToDo temp hard-code style */
	const auto& textEditStyle = "QPlainTextEdit, QTextEdit{font-style: normal;font-size: 12pt;font-family: \"Liberation Mono\";\
padding: 3px;border: 1px solid rgba(255, 255, 255, 255);\
background: rgba(045, 045, 045, 255);alternate-background-color: rgba(070, 070, 070, 255);\
color: rgba(255, 255, 255, 255);}";
	m_TagDescriptionView->setStyleSheet(textEditStyle);
}

void MainWindow::SearchTextByType(const QString& searchText, const QString& filterType)
{
	const auto findTypeIt = std::find(modelPropertyNames.begin(), modelPropertyNames.end(), filterType);
	if(findTypeIt != modelPropertyNames.end())
	{
		const auto columnType = std::distance(modelPropertyNames.begin(), findTypeIt);
		if(columnType == SettingsColumnsType::Description)
		{
			m_FilterDataModel.setFilterKeyColumn(SettingsColumnsType::Begin);
			m_FilterDataModel.setFilterRole(Qt::UserRole);
		}
		else
		{
			m_FilterDataModel.setFilterKeyColumn(columnType);
		}
	}
	m_FilterDataModel.FilterData(searchText);
	if(searchText.isEmpty())
	{
		m_SettingsView->expandAll();
	}
}
