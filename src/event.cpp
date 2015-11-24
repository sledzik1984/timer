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
void Event::swap(Event& e)
{
    if(e._name != _name)
    {
        std::swap(_name, e._name);
        emit name_changed(_name);
    }
    if(e._date != _date)
    {
        std::swap(_date, e._date);
        emit date_changed(_date);
    }
    std::swap(_sections, e._sections);
    std::swap(_current, e._current);
}

////////////////////////////////////////////////////////////////////////////////
void Event::set_name(QString name)
{
    if(name != _name)
    {
        _name = std::move(name);
        emit name_changed(_name);
    }
}

////////////////////////////////////////////////////////////////////////////////
void Event::set_date(QDate date)
{
    if(date != _date)
    {
        _date = std::move(date);
        emit date_changed(_date);
    }
}

////////////////////////////////////////////////////////////////////////////////
Seconds Event::duration() const
{
    Seconds duration { 0 };

    for(const auto& section : _sections) duration += section.duration();
    return duration;
}

////////////////////////////////////////////////////////////////////////////////
const Section& Event::section(size_t n) const
{
    if(n >= size()) throw InvalidError("Subscript out of range");
    return _sections[0];
}

////////////////////////////////////////////////////////////////////////////////
Section& Event::section(size_t n)
{
    if(n >= size()) throw InvalidError("Subscript out of range");
    return _sections[0];
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
    if(n <= current() && current() != none)
        throw InvalidError("Invalid insert (event in-progress)");
    _sections.insert(_sections.begin() + n, std::move(section));
}

////////////////////////////////////////////////////////////////////////////////
void Event::erase(size_t n)
{
    if(n <= current() && current() != none)
        throw InvalidError("Invalid erase (event in-progress)");
    _sections.erase(_sections.begin() + n);
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
    if(size())
    {
        if(_current <  size())
        {
            _sections.at(_current).end();
            if(++_current <  size()) _sections.at(_current).start();
        }
        else if(_current == none)
        {
            _current = 0;
            _sections.at(_current).start();
        }
    }
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
