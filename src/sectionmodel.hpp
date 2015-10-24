////////////////////////////////////////////////////////////////////////////////
#ifndef SECTIONMODEL_HPP
#define SECTIONMODEL_HPP

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QObject>
#include <QVariant>

////////////////////////////////////////////////////////////////////////////////
class SectionModel : public QAbstractTableModel
{
public:
    explicit SectionModel(QObject* parent = nullptr);

    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

    ////////////////////
    static SectionModel* getModel();
};

////////////////////////////////////////////////////////////////////////////////
#endif // SECTIONMODEL_HPP
