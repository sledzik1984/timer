////////////////////////////////////////////////////////////////////////////////
#ifndef TIMEDELEGATE_HPP
#define TIMEDELEGATE_HPP

#include <QObject>
#include <QStyledItemDelegate>

////////////////////////////////////////////////////////////////////////////////
class TimeDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    TimeDelegate(QObject* parent = nullptr);

    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex&) const override;

    virtual void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

    virtual void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

////////////////////////////////////////////////////////////////////////////////
#endif // TIMEDELEGATE_HPP
