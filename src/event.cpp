////////////////////////////////////////////////////////////////////////////////
#include "error.hpp"
#include "event.hpp"

////////////////////////////////////////////////////////////////////////////////
Event::Event(QString name, QDate date)
{
    set_name(std::move(name));
    set_date(std::move(date));
}

////////////////////////////////////////////////////////////////////////////////
Seconds Event::duration() const
{
    Seconds duration { 0 };

    for(const auto& section : _sections) duration += section.duration();
    return duration;
}

////////////////////////////////////////////////////////////////////////////////
void Event::clear()
{
    _sections.clear();
    _current = none;
}

////////////////////////////////////////////////////////////////////////////////
void Event::insert(size_t n, Section section)
{
    if(current() == none || current() < n)
        _sections.insert(_sections.begin() + n, std::move(section));
    else throw InvalidError("Invalid insert (event in-progress)");
}

////////////////////////////////////////////////////////////////////////////////
void Event::erase(size_t n)
{
    if(current() == none || current() < n)
        _sections.erase(_sections.begin() + n);
    else throw InvalidError("Invalid erase (event in-progress)");
}

////////////////////////////////////////////////////////////////////////////////
void Event::reset()
{
    for(auto& section : _sections) section.reset();
    _current = none;
}

////////////////////////////////////////////////////////////////////////////////
void Event::next()
{
    if(current() == none)
    {
        _current = 0;
    }
    else if(current() < size())
    {
        _sections.at(current()).end();
        ++_current;
    }

    if(current() < size()) _sections.at(current()).start();
}

////////////////////////////////////////////////////////////////////////////////
Seconds Event::overage() const
{
    Seconds overage { 0 };

    for(const auto& section : _sections) overage += section.overage();
    return overage;
}

////////////////////////////////////////////////////////////////////////////////
Event& Event::instance()
{
    static Event event;
    return event;
}
