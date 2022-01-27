#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "StableDeclaration.h"
#include "SettingsTreeView.h"
#include "SettingsModel.h"
#include "FilterDataModel.h"

namespace Ui {
class MainWindow;
}

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
    void AddMenuBar();
    void SetStyleSheet();
	QMenu* CreateFileMenu();
	QMenu* CreateSearchMenu();
private:
    QVBoxLayout* m_MainLayout;
	SettingsTreeView* m_SettingsView;
	QPlainTextEdit* m_TagDescriptionView;
	WdgSearch* m_WdgSearch;
	SettingsModel m_SourceModel;
    FilterDataModel m_FilterDataModel;
    QString m_lasSelectedPath;

};

#endif // MAINWINDOW_H
