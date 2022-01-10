#include "GeneralItemsDelegate.h"
#include <QModelIndex>
#include <QComboBox>

GeneralItemsDelegate::GeneralItemsDelegate(QObject *parent)
	: QItemDelegate(parent)
{

}

QWidget* GeneralItemsDelegate::createEditor(QWidget* parent,
	const QStyleOptionViewItem& option ,
	const QModelIndex& index) const
{
	auto value = index.model()->data(index, Qt::EditRole);
	if(value.type() == QVariant::StringList)
	{
		createListEditor(parent, option, index);
	}
	return QItemDelegate::createEditor(parent, option, index);
}

QWidget* GeneralItemsDelegate::createListEditor(QWidget* parent,
											const QStyleOptionViewItem& /*option*/ ,
											const QModelIndex& /*index*/) const
{
	auto editor = new QComboBox(parent);
	editor->setFrame(false);
	return editor;
}

void GeneralItemsDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
	auto value = index.model()->data(index, Qt::EditRole);
	if(value.type() == QVariant::StringList)
	{
		setListEditorData(editor, index);
	}
	QItemDelegate::setEditorData(editor, index);
}

void GeneralItemsDelegate::setListEditorData(QWidget *editor,
										 const QModelIndex &index) const
{
	auto value = index.model()->data(index, Qt::EditRole);
	auto comboBox = static_cast<QComboBox*>(editor);
	comboBox->addItems(value.toStringList());
}

void GeneralItemsDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
								   const QModelIndex& index) const
{
	auto value = index.model()->data(index, Qt::EditRole);
	if(value.type() == QVariant::StringList)
	{
		setListModelData(editor, model, index);
		return;
	}
	QItemDelegate::setModelData(editor, model, index);
}

void GeneralItemsDelegate::setListModelData(QWidget* editor, QAbstractItemModel* model,
										const QModelIndex& index) const
{
	auto comboBox = static_cast<QComboBox*>(editor);
	auto currentText = comboBox->currentText();

	auto newListData = index.model()->data(index, Qt::EditRole).toStringList();
	auto firstElement = newListData.begin();
	auto curElement = std::find(newListData.begin(), newListData.end(), currentText);
	std::swap(*firstElement, *curElement);

	model->setData(index, newListData, Qt::EditRole);
}

void GeneralItemsDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& /*index*/) const
{
	editor->setGeometry(option.rect);
}
