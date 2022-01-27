#ifndef WDGSEARCH_H
#define WDGSEARCH_H
#include "StableDeclaration.h"
#include <QFrame>

class WdgSearch : public QFrame
{
    Q_OBJECT
public:
    explicit WdgSearch(QWidget *parent = nullptr);
	void addFilterType(const QString& type);
signals:
	void SearchTextByType(const QString&, const QString&);
private slots:
	void MakeTextSearch();
private:
	void showEvent(QShowEvent *event) override;
    void SetStyleSheet();
private:
	QComboBox* m_SearchType;
    QLineEdit* m_SearchEdit;
    QPushButton* m_SearchBtn;
};

#endif // WDGSEARCH_H
