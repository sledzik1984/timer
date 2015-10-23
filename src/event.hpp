////////////////////////////////////////////////////////////////////////////////
#ifndef EVENT_HPP
#define EVENT_HPP

#include "section.hpp"

#include <QObject>
#include <QString>

#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
typedef std::vector<Section> Sections;

////////////////////////////////////////////////////////////////////////////////
class Event : public QObject
{
    Q_OBJECT

public:
    explicit Event(QString name) :
        _name(std::move(name))
    { }

    ////////////////////
    void set_name(QString name)
    {
        _name = std::move(name);
        emit name_changed(_name);
    }

    const QString& name() const noexcept { return _name; }

signals:
    void name_changed(const QString&);

private:
    QString _name;
    Sections _sections;
};

////////////////////////////////////////////////////////////////////////////////
#endif // EVENT_HPP
