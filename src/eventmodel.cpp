////////////////////////////////////////////////////////////////////////////////
#include "eventmodel.hpp"

#include <QFile>

////////////////////////////////////////////////////////////////////////////////
enum Column { Num, Name, Time, Size };

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
    if(role == Qt::DisplayRole)
    {
        int row = index.row();
        switch(index.column())
        {
        case Column::Num : return row + 1;
        case Column::Name: return _event.section(row).name();
        case Column::Time: return _event.section(row).time();
        }
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
    return false;
}

////////////////////////////////////////////////////////////////////////////////
Qt::ItemFlags EventModel::flags(const QModelIndex& index) const
{
    return QAbstractTableModel::flags(index);
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
