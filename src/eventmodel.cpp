////////////////////////////////////////////////////////////////////////////////
#include "eventmodel.hpp"

#include <QFile>

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
    return parent.isValid() ? 0 : Column::Size;
}

////////////////////////////////////////////////////////////////////////////////
int EventModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : _event.sections().size();
}

////////////////////////////////////////////////////////////////////////////////
QVariant EventModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();

    switch(role)
    {
    case Qt::DisplayRole:
        switch(column)
        {
        case Column::Num : return row + 1;
        case Column::Name: return _event.section(row).name();
        case Column::Time: return _event.section(row).time().toString("h:mm:ss");
        }
        break;

    case Qt::EditRole:
        switch(column)
        {
        case Column::Name: return _event.section(row).name();
        case Column::Time: return _event.section(row).time();
        }
        break;

    case Qt::TextAlignmentRole:
        switch(column)
        {
        case Column::Num : return Qt::AlignCenter;
        case Column::Name: return Qt::AlignLeft;
        case Column::Time: return Qt::AlignRight;
        }
        break;
    }

    return QVariant();
}

////////////////////////////////////////////////////////////////////////////////
QVariant EventModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
        switch(section)
        {
        case Column::Num : return "#";
        case Column::Name: return "Name";
        case Column::Time: return "Time";
        }

    return QVariant();
}

////////////////////////////////////////////////////////////////////////////////
bool EventModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    int row = index.row();
    int column = index.column();

    bool changed = false;

    if(role == Qt::EditRole)
    {
        switch(column)
        {
        case Column::Name:
            _event.section(row).set_name(value.toString());
            changed = true;
            break;

        case Column::Time:
            _event.section(row).set_time(value.toTime());
            changed = true;
            break;
        }
    }

    if(changed) emit dataChanged(index, index);
    return changed;
}

////////////////////////////////////////////////////////////////////////////////
Qt::ItemFlags EventModel::flags(const QModelIndex& index) const
{
    int column = index.column();

    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if(column == Column::Name || column == Column::Time) flags |= Qt::ItemIsEditable;

    return flags;
}

////////////////////////////////////////////////////////////////////////////////
void EventModel::clear()
{
    beginResetModel();

    _filename.clear();
    emit filename_changed(_filename);

    _event.clear();
    emit name_changed(_event.name());

    endResetModel();
}

////////////////////////////////////////////////////////////////////////////////
void EventModel::open(QString filename)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly)) throw QString("Failed to open file for reading");

    beginResetModel();

    _filename = std::move(filename);
    emit filename_changed(_filename);

    QXmlStreamReader reader(&file);
    _event.read(reader);
    emit name_changed(_event.name());

    endResetModel();

    if(reader.hasError()) throw reader.errorString();
}

////////////////////////////////////////////////////////////////////////////////
void EventModel::save()
{
    if(_filename.size())
    {
        QFile file(_filename);
        if(!file.open(QFile::WriteOnly)) throw QString("Failed to open file for writing");

        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);

        _event.write(writer);

        if(writer.hasError()) throw file.errorString();
    }
}

////////////////////////////////////////////////////////////////////////////////
void EventModel::save_as(QString filename)
{
    std::swap(_filename, filename);
    try
    {
        save();
        emit filename_changed(_filename);
    }
    catch(...)
    {
        std::swap(_filename, filename);
        throw;
    }
}

////////////////////////////////////////////////////////////////////////////////
bool EventModel::insertRows(int row, int count, const QModelIndex& parent)
{
    if(parent.isValid() || row < 0 || row > (int)_event.sections().size()) return false;

    beginInsertRows(parent, row, row + count - 1);
    for(; count; --count)
    {
        _event.insert(row);
        emit dataChanged(index(row, 0, parent), index(row, columnCount(parent) - 1));
    }
    endInsertRows();

    return true;
}
