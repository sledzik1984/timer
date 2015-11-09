////////////////////////////////////////////////////////////////////////////////
#ifndef EVENT_HPP
#define EVENT_HPP

#include "section.hpp"

#include <QString>

#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
class Event
{
public:
    using Sections = std::vector<Section>;

    ////////////////////
    Event() { reset(); }
    explicit Event(QString name);

    ////////////////////
    Event(const Event&) = default;
    Event(Event&&) = default;

    Event& operator=(const Event&) = default;
    Event& operator=(Event&&) = default;

    ////////////////////
    void set_name(QString name) { _name = std::move(name); }
    const QString& name() const noexcept { return _name; }

    const Section::Duration duration() const;

    ////////////////////
    size_t size() const noexcept { return _sections.size(); }
    bool empty() const noexcept { return _sections.empty(); }
    void clear() { _sections.clear(); }

    const Section& section(size_t n) const noexcept { return _sections.at(n); }
    size_t current() const noexcept { return _current; }

    ////////////////////
    void reset();
    void next();

    const Section::Timepoint& started() const noexcept { return section(0).started(); }
    const Section::Timepoint& ended() const noexcept { return section(size() - 1).ended(); }

    bool is_started() const noexcept { return section(0).is_started(); }
    bool is_ended() const noexcept { return section(size() - 1).is_ended(); }

    const Section::Duration overage() const;

private:
    QString _name;
    Sections _sections;

    friend class EventReader;
    friend class EventWriter;
    friend class EventModel;

    size_t _current = none;

    static constexpr size_t none = -1;
};

////////////////////////////////////////////////////////////////////////////////
#endif // EVENT_HPP
