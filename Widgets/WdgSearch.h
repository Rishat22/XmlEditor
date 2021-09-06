#ifndef WDGSEARCH_H
#define WDGSEARCH_H
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QString>
#include <QWidget>

class WdgSearch : public QWidget
{
    Q_OBJECT
public:
    explicit WdgSearch(QWidget *parent = nullptr);

signals:
    void TextSearch(const QString&);
private:
    void SetStyleSheet();
private:
    QLineEdit* m_SearchEdit;
    QPushButton* m_SearchBtn;
    QHBoxLayout* m_MainLayout;
};

#endif // WDGSEARCH_H
