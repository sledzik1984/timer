////////////////////////////////////////////////////////////////////////////////
#include "event.hpp"

////////////////////////////////////////////////////////////////////////////////
Event::Event(QString name, QDate date)
{
    set_name(std::move(name));
    set_date(std::move(date));
    reset();
}

////////////////////////////////////////////////////////////////////////////////
Section::Duration Event::duration() const
{
    Section::Duration duration { 0 };

    for(const auto& section : _sections) duration += section.duration();
    return duration;
}

////////////////////////////////////////////////////////////////////////////////
void Event::reset()
{
    _current = none;
    for(auto& section : _sections) section.reset();
}

////////////////////////////////////////////////////////////////////////////////
void Event::next()
{
    if(current() < size())
    {
        _sections.at(current()).end();
        if(++_current < size()) _sections.at(current()).start();
    }
}

////////////////////////////////////////////////////////////////////////////////
Section::Duration Event::overage() const
{
    Section::Duration overage { 0 };

    for(const auto& section : _sections) overage += section.overage();
    return overage;
}
