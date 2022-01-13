#ifndef SETTINGSTREEVIEW_H
#define SETTINGSTREEVIEW_H
#include <QObject>
#include <QTreeView>

class SettingsTreeView : public QTreeView
{
	Q_OBJECT
public:
        explicit SettingsTreeView(QWidget* parent = nullptr);
signals:
    void showDescription(const QString& description);

private slots:
    void objectClicked(const QModelIndex &index);
private:
    void SetStyleSheet();
};

#endif // SETTINGSTREEVIEW_H
