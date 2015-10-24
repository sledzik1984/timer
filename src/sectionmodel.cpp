////////////////////////////////////////////////////////////////////////////////
#include "sectionmodel.hpp"

////////////////////////////////////////////////////////////////////////////////
SectionModel* SectionModel::getModel()
{
    static SectionModel model;
    return &model;
}

////////////////////////////////////////////////////////////////////////////////
SectionModel::SectionModel(QObject* parent)
{
    //
}

////////////////////////////////////////////////////////////////////////////////
int SectionModel::columnCount(const QModelIndex& parent) const
{
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
int SectionModel::rowCount(const QModelIndex& parent) const
{
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
QVariant SectionModel::data(const QModelIndex& index, int role) const
{
    return QVariant();
}

////////////////////////////////////////////////////////////////////////////////
QVariant SectionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

////////////////////////////////////////////////////////////////////////////////
bool SectionModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    return false;
}

////////////////////////////////////////////////////////////////////////////////
Qt::ItemFlags SectionModel::flags(const QModelIndex& index) const
{
    return QAbstractTableModel::flags(index);
}