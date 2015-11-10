////////////////////////////////////////////////////////////////////////////////
#ifndef EVENT_HPP
#define EVENT_HPP

#include "section.hpp"

#include <QDate>
#include <QString>

#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
using Sections = std::vector<Section>;

////////////////////////////////////////////////////////////////////////////////
class Event
{
public:
    ////////////////////
    Event() { reset(); }
    Event(QString name, QDate date);

    ////////////////////
    Event(const Event&) = default;
    Event(Event&&) = default;

    Event& operator=(const Event&) = default;
    Event& operator=(Event&&) = default;

    ////////////////////
    void set_name(QString name) { _name = std::move(name); }
    const QString& name() const noexcept { return _name; }

    void set_date(QDate date) { _date = std::move(date); }
    const QDate& date() const noexcept { return _date; }

    Section::Duration duration() const;

    ////////////////////
    size_t size() const noexcept { return _sections.size(); }
    bool empty() const noexcept { return _sections.empty(); }
    void clear() { _sections.clear(); }

    const Section& section(size_t n) const noexcept { return _sections.at(n); }
    size_t current() const noexcept { return _current; }

    ////////////////////
    void reset();
    void next();

    const QDateTime& started() const noexcept { return section(0).started(); }
    const QDateTime& ended() const noexcept { return section(size() - 1).ended(); }

    bool is_started() const noexcept { return section(0).is_started(); }
    bool is_ended() const noexcept { return section(size() - 1).is_ended(); }

    Section::Duration overage() const;

private:
    QString _name;
    QDate _date;
    Sections _sections;

    size_t _current = none;

    static constexpr size_t none = -1;

    friend class EventReader;
    friend class EventWriter;

    ////////////////////
    static QString to_string(const QDate&);
    static QDate to_date(const QString&);
};

////////////////////////////////////////////////////////////////////////////////
#endif // EVENT_HPP
