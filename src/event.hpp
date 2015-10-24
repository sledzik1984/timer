////////////////////////////////////////////////////////////////////////////////
#ifndef EVENT_HPP
#define EVENT_HPP

#include "section.hpp"

#include <QString>

#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
typedef std::vector<Section> Sections;

////////////////////////////////////////////////////////////////////////////////
class Event
{
public:
    ////////////////////
    Event() = default;
    explicit Event(QString name) { set_name(std::move(name)); }

    ////////////////////
    Event(const Event&) = default;
    Event(Event&&) = default;

    Event& operator=(const Event&) = default;
    Event& operator=(Event&&) = default;

    ////////////////////
    void set_name(QString name) { _name = std::move(name); }
    const QString& name() const noexcept { return _name; }

private:
    QString _name;
    Sections _sections;
};

////////////////////////////////////////////////////////////////////////////////
#endif // EVENT_HPP
