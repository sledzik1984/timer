////////////////////////////////////////////////////////////////////////////////
#ifndef EVENT_HPP
#define EVENT_HPP

#include "section.hpp"
#include <QString>

#include <chrono>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
using Sections = std::vector<Section>;

using Clock = std::chrono::system_clock;
using Timepoint = std::chrono::time_point<Clock>;

////////////////////////////////////////////////////////////////////////////////
class Event
{
public:
    ////////////////////
    Event() { reset(); }
    Event(QString name, Timepoint date);

    ////////////////////
    Event(const Event&) = default;
    Event(Event&&) = default;

    Event& operator=(const Event&) = default;
    Event& operator=(Event&&) = default;

    ////////////////////
    void set_name(QString name) { _name = std::move(name); }
    const QString& name() const noexcept { return _name; }

    void set_date(Timepoint date) { _date = std::move(date); }
    const Timepoint& date() const noexcept { return _date; }

    const Duration duration() const;

    ////////////////////
    size_t size() const noexcept { return _sections.size(); }
    bool empty() const noexcept { return _sections.empty(); }
    void clear() { _sections.clear(); }

    const Section& section(size_t n) const noexcept { return _sections.at(n); }
    size_t current() const noexcept { return _current; }

    ////////////////////
    void reset();
    void next();

    const Timepoint& started() const noexcept { return section(0).started(); }
    const Timepoint& ended() const noexcept { return section(size() - 1).ended(); }

    bool is_started() const noexcept { return section(0).is_started(); }
    bool is_ended() const noexcept { return section(size() - 1).is_ended(); }

    const Duration overage() const;

private:
    QString _name;
    Timepoint _date;
    Sections _sections;

    friend class EventReader;
    friend class EventModel;

    size_t _current = none;

    static constexpr size_t none = -1;
};

////////////////////////////////////////////////////////////////////////////////
#endif // EVENT_HPP
