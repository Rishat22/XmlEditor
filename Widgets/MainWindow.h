#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "StableDeclaration.h"
#include "SettingsTreeView.h"
#include "SettingsModel.h"
#include "FilterDataModel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void SetDescriptionText(const QString& descriptionText);
	void SearchTextByType(const QString& searchText, const QString& filterType);
    void saveData(const std::string& strFileName);
    void loadData(const std::string& strFileName);

private:
	static void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);
    void AddMenuBar();
    void SetStyleSheet();
	QMenu* CreateFileMenu();
	QMenu* CreateSearchMenu();
private:
	SettingsTreeView* m_SettingsView;
	QPlainTextEdit* m_TagDescriptionView;
	QPlainTextEdit* m_LogsInfoView;
	WdgSearch* m_WdgSearch;
	SettingsModel m_SourceModel;
    FilterDataModel m_FilterDataModel;
    QString m_lasSelectedPath;

};

#endif // MAINWINDOW_H
