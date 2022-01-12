#include "GeneralItemsDelegate.h"
#include <QModelIndex>
#include <QComboBox>
#include <QColorDialog>

GeneralItemsDelegate::GeneralItemsDelegate(QObject *parent)
	: QItemDelegate(parent)
{

}

QWidget* GeneralItemsDelegate::createEditor(QWidget* parent,
	const QStyleOptionViewItem& option ,
	const QModelIndex& index) const
{
	auto value = index.model()->data(index, Qt::EditRole);
	switch (value.type())
	{
		case QVariant::StringList :
		{
			auto editor = new QComboBox(parent);
			editor->setFrame(false);
			return editor;
		}
		case QVariant::Color :
		{
			auto ColorDialog = new QColorDialog(parent);
			ColorDialog->setOption(QColorDialog::ShowAlphaChannel, true);
			ColorDialog->setOption(QColorDialog::DontUseNativeDialog, true);
			return ColorDialog;
		}
		default:
			return QItemDelegate::createEditor(parent, option, index);
	}
	return QItemDelegate::createEditor(parent, option, index);
}

void GeneralItemsDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
	auto value = index.model()->data(index, Qt::EditRole);
	switch (value.type())
	{
		case QVariant::StringList :
		{
			auto value = index.model()->data(index, Qt::EditRole);
			auto comboBox = static_cast<QComboBox*>(editor);
			comboBox->addItems(value.toStringList());
			return;
		}
		case QVariant::Color :
		{
			auto value = index.model()->data(index, Qt::EditRole);
			auto colorEditor = static_cast<QColorDialog*>(editor);
			colorEditor->setCurrentColor(value.value<QColor>());
			return;
		}
		default:
			QItemDelegate::setEditorData(editor, index);
	}
	QItemDelegate::setEditorData(editor, index);
}

void GeneralItemsDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
								   const QModelIndex& index) const
{
	auto value = index.model()->data(index, Qt::EditRole);
	switch (value.type())
	{
		case QVariant::StringList :
		{
			return setListModelData(editor, model, index);
		}
		case QVariant::Color :
		{
			auto colorEditor = static_cast<QColorDialog*>(editor);
			const QColor& currentColor = colorEditor->currentColor();
			model->setData(index, currentColor, Qt::EditRole);
			return;
		}
		default:
			return QItemDelegate::setModelData(editor, model, index);
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
