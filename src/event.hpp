////////////////////////////////////////////////////////////////////////////////
#ifndef EVENT_HPP
#define EVENT_HPP

////////////////////////////////////////////////////////////////////////////////
#include "section.hpp"

#include <QDate>
#include <QDateTime>
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

    Seconds duration() const;

    ////////////////////
    size_t size() const noexcept { return _sections.size(); }

    const Section& section(size_t n) const;
    Section& section(size_t n);

    void clear();

    void insert(size_t n, Section section);
    void insert(Section section) { insert(size(), std::move(section)); }

    void erase(size_t n);

    ////////////////////
    void reset();
    void next();

    size_t current() const noexcept { return _current; }
    static constexpr size_t none = -1;

    const QDateTime& started() const { return section(0).started(); }
    const QDateTime& ended() const { return section(size() - 1).ended(); }

    bool is_started() const { return size() && section(0).is_started(); }
    bool is_ended() const { return size() && section(size() - 1).is_ended(); }

    Seconds overage() const;

    static Event& instance();

private:
    QString _name;
    QDate _date;
    Sections _sections;

    size_t _current = none;
};

////////////////////////////////////////////////////////////////////////////////
#endif // EVENT_HPP
