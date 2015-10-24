////////////////////////////////////////////////////////////////////////////////
#include "eventmodel.hpp"

#include <vector>

////////////////////////////////////////////////////////////////////////////////
const std::vector<QString> headers =
{
    "#", "Name", "Time", "",
};

////////////////////////////////////////////////////////////////////////////////
EventModel* EventModel::get_model()
{
    static EventModel model;
    return &model;
}

////////////////////////////////////////////////////////////////////////////////
EventModel::EventModel(QObject* parent) :
    QAbstractTableModel(parent)
{
    //
}

////////////////////////////////////////////////////////////////////////////////
int EventModel::columnCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : headers.size();
}

////////////////////////////////////////////////////////////////////////////////
int EventModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : event.sections().size();
}

////////////////////////////////////////////////////////////////////////////////
QVariant EventModel::data(const QModelIndex& index, int role) const
{
    return QVariant();
}

////////////////////////////////////////////////////////////////////////////////
QVariant EventModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return orientation == Qt::Horizontal
        && role == Qt::DisplayRole
        && (size_t)section < headers.size() ? headers[section]
                                            : QVariant();
}

////////////////////////////////////////////////////////////////////////////////
bool EventModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    return false;
}

////////////////////////////////////////////////////////////////////////////////
Qt::ItemFlags EventModel::flags(const QModelIndex& index) const
{
    return QAbstractTableModel::flags(index);
}