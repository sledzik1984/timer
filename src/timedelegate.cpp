////////////////////////////////////////////////////////////////////////////////
#include "timedelegate.hpp"

#include <QTimeEdit>

////////////////////////////////////////////////////////////////////////////////
TimeDelegate::TimeDelegate(QObject* parent) : QStyledItemDelegate(parent)
{
    //
}

////////////////////////////////////////////////////////////////////////////////
QWidget* TimeDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex&) const
{
    QTimeEdit* editor = new QTimeEdit(parent);

    editor->setMinimumTime(QTime(0, 0));
    editor->setMaximumTime(QTime(23, 59, 59));
    editor->setDisplayFormat("h:mm:ss");

    return editor;
}

////////////////////////////////////////////////////////////////////////////////
void TimeDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    static_cast<QTimeEdit*>(editor)->setTime(index.data(Qt::EditRole).toTime());
}

////////////////////////////////////////////////////////////////////////////////
void TimeDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    model->setData(index, static_cast<QTimeEdit*>(editor)->time(), Qt::DisplayRole);
}

////////////////////////////////////////////////////////////////////////////////
void TimeDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex&) const
{
    editor->setGeometry(option.rect);
}
