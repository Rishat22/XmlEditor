#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "StableDeclaration.h"
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
    void BtnSearchClicked(const QString& text);
    void saveData(const std::string& strFileName);
    void loadData(const std::string& strFileName);
private:
    void AddMenuBar();
    void SetStyleSheet();
    QList<QAction*> CreateFileActions();
private:
    QVBoxLayout* m_MainLayout;
    QTreeView* m_TreeView;
    WdgSearch* m_WdgSearch;
	SettingsModel m_SourceModel;
    FilterDataModel m_FilterDataModel;
    QString m_lasSelectedPath;

};

#endif // MAINWINDOW_H
