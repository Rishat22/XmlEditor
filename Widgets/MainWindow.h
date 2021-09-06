#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "FilterDataModel.h"
#include "WdgSearch.h"

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
private:
	void SetStyleSheet();
private:
	QVBoxLayout* m_MainLayout;
//	QStand* m_SourceModel;
	QTreeView* m_TreeView;
	WdgSearch* m_WdgSearch;
	FilterDataModel m_FilterDataModel;

};

#endif // MAINWINDOW_H
