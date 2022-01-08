#include "ListItemDelegate.h"
#include <QModelIndex>
#include <QComboBox>

ListItemDelegate::ListItemDelegate(QObject *parent)
	: QItemDelegate(parent)
{

}

QWidget* ListItemDelegate::createEditor(QWidget* parent,
	const QStyleOptionViewItem& /* option */,
	const QModelIndex& /* index */) const
{
	auto editor = new QComboBox(parent);
	editor->setFrame(false);

    return editor;
}

void ListItemDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
	auto value = index.model()->data(index, Qt::EditRole);
	auto comboBox = static_cast<QComboBox*>(editor);
	comboBox->addItems(value.toStringList());
}

void ListItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
								   const QModelIndex& index) const
{
	auto comboBox = static_cast<QComboBox*>(editor);
	auto currentText = comboBox->currentText();
	model->setData(index, currentText, Qt::EditRole);
}

void ListItemDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& /*index*/) const
{
	editor->setGeometry(option.rect);
}
