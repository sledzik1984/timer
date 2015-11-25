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
void Event::replace(Event::Pointer&& e)
{
    set_name(std::move(e->_name));
    set_date(std::move(e->_date));

    _sections = std::move(e->_sections);
    update_duration();
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
    Seconds duration = 0;
    for(const auto& section : _sections) duration += section->duration();
    return duration;
}

////////////////////////////////////////////////////////////////////////////////
const Section::Pointer& Event::section(size_t n) const
{
    if(n >= size()) throw InvalidError("Event::Section: Subscript out of range");
    return _sections[0];
}

////////////////////////////////////////////////////////////////////////////////
Section::Pointer& Event::section(size_t n)
{
    if(n >= size()) throw InvalidError("Event::Section: Subscript out of range");
    return _sections[0];
}

////////////////////////////////////////////////////////////////////////////////
void Event::clear()
{
    // erase sections one by one
    // starting at the end
    while(size()) erase(size() - 1);
}

////////////////////////////////////////////////////////////////////////////////
void Event::insert(size_t n, Section::Pointer section)
{
    if(n > size()) throw InvalidError("Event::insert: Subscript out of range");

    auto ri = _sections.begin() + n;
    if(n < size() && (*ri)->is_started()) throw InvalidError("Event::insert: Invalid insert");

    _sections.insert(ri, std::move(section));
    emit section_inserted(n);

    connect(&*section, &Section::duration_changed, this, &Event::update_duration);
    update_duration();
}

////////////////////////////////////////////////////////////////////////////////
void Event::erase(size_t n)
{
    if(n > size()) throw InvalidError("Event::erase: Subscript out of range");

    auto ri = _sections.begin() + n;
    if(n < size() && (*ri)->is_started()) throw InvalidError("Event::erase: Invalid erase");

    _sections.erase(ri);
    emit section_erased(n);

    update_duration();
}

////////////////////////////////////////////////////////////////////////////////
QDateTime Event::started() const
{
    QDateTime started;
    if(size()) started = section(0)->started();
    return started;
}

////////////////////////////////////////////////////////////////////////////////
QDateTime Event::ended() const
{
    QDateTime ended;
    if(size()) ended = section(size() - 1)->ended();
    return ended;
}

////////////////////////////////////////////////////////////////////////////////
Seconds Event::overage() const
{
    Seconds overage = 0;
    for(const auto& section : _sections) overage += section->overage();
    return overage;
}

////////////////////////////////////////////////////////////////////////////////
void Event::start()
{
    if(!is_started() && size()) section(0)->start();
}

////////////////////////////////////////////////////////////////////////////////
void Event::next()
{
}

////////////////////////////////////////////////////////////////////////////////
void Event::reset()
{
    for(auto& section : _sections) section->reset();
}

////////////////////////////////////////////////////////////////////////////////
void Event::update_duration()
{
    emit duration_changed(duration());
}

////////////////////////////////////////////////////////////////////////////////
Event::Pointer Event::instance()
{
    static Event::Pointer event(new Event());
    return event;
}
