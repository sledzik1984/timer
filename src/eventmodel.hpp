////////////////////////////////////////////////////////////////////////////////
#ifndef EVENTMODEL_HPP
#define EVENTMODEL_HPP

#include "event.hpp"

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QObject>
#include <QString>
#include <QVariant>

#include <utility>

////////////////////////////////////////////////////////////////////////////////
enum Column { Num, Name, Time, Size };

////////////////////////////////////////////////////////////////////////////////
class EventModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit EventModel(QObject* parent = nullptr);

    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

    ////////////////////
    void clear();
    void open(QString filename);
    void save();
    void save_as(QString filename);

    ////////////////////
    void set_name(QString name)
    {
        _event.set_name(std::move(name));
        emit name_changed(_event.name());
    }
    const QString& name() const noexcept { return _event.name(); }

    const QString& filename() const noexcept { return _filename; }

    ////////////////////
    static EventModel* get_model();

signals:
    void filename_changed(const QString&);
    void name_changed(const QString&);

private:
    QString _filename;
    Event _event;
};

////////////////////////////////////////////////////////////////////////////////
#endif // EVENTMODEL_HPP
