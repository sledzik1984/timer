////////////////////////////////////////////////////////////////////////////////
#include "error.hpp"
#include "event.hpp"

////////////////////////////////////////////////////////////////////////////////
class ProgressError : public InvalidError
{
public:
    ProgressError(QString proc) :
        InvalidError(std::move(proc.append(": Event in-progress")))
    { }
};

class RangeError : public InvalidError
{
public:
    RangeError(QString proc) :
        InvalidError(std::move(proc.append(": Index out of range")))
    { }
};

////////////////////////////////////////////////////////////////////////////////
Event::Event(QString name, QDate date)
{
    set_name(std::move(name));
    set_date(std::move(date));
}

////////////////////////////////////////////////////////////////////////////////
void Event::replace(Event::Pointer&& e)
{
    if(started().isValid() || e->started().isValid()) throw ProgressError("Event::replace");

    set_name(std::move(e->_name));
    set_date(std::move(e->_date));

    clear();

    for(auto ri = e->begin(); ri != e->end(); ++ri) insert(end(), std::move(*ri));
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
Seconds Event::period() const
{
    Seconds seconds = 0;
    for(const auto& section : _sections) seconds += section->period();
    return seconds;
}

////////////////////////////////////////////////////////////////////////////////
Seconds Event::real_period() const
{
    Seconds seconds = 0;
    for(const auto& section : _sections) seconds += section->real_period();
    return seconds;
}

////////////////////////////////////////////////////////////////////////////////
const Section::Pointer& Event::section(size_t n) const
{
    if(n >= size()) throw RangeError("Event::section");
    return _sections[n];
}

////////////////////////////////////////////////////////////////////////////////
Section::Pointer& Event::section(size_t n)
{
    if(n >= size()) throw RangeError("Event::section");
    return _sections[n];
}

////////////////////////////////////////////////////////////////////////////////
void Event::clear()
{
    if(started().isValid()) throw ProgressError("Event::clear");

    set_current(none);
    while(size()) erase(rbegin().base());
}

////////////////////////////////////////////////////////////////////////////////
void Event::insert(size_t n, Section::Pointer section)
{
    if(n >  size()) throw RangeError("Event::insert");
    if(static_cast<int>(n) <= current()) throw ProgressError("Event::insert");

    insert(begin() + n, std::move(section));
}

////////////////////////////////////////////////////////////////////////////////
void Event::erase(size_t n)
{
    if(n >= size()) throw RangeError("Event::erase");
    if(static_cast<int>(n) <= current()) throw ProgressError("Event::erase");

    erase(begin() + n);
}

////////////////////////////////////////////////////////////////////////////////
QDateTime Event::started() const
{
    QDateTime started;
    if(size()) started = (*begin())->started();
    return started;
}

////////////////////////////////////////////////////////////////////////////////
QDateTime Event::ended() const
{
    QDateTime ended;
    if(size()) ended = (*rbegin())->ended();
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
bool Event::start()
{
    if(current() == none && size())
    {
        auto section = this->section(0);
        section->start();
        emit started_changed(section->started());

        set_current(0);
        return true;
    }
    else return false;
}

////////////////////////////////////////////////////////////////////////////////
bool Event::next()
{
    if(current() != none)
    {
        auto s = section(current());
        s->end();

        size_t next = current() + 1;
        if(next < size())
        {
            section(next)->start();
            set_current(next);
        }
        else
        {
            set_current(none);
            emit ended_changed(s->ended());
        }

        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////
void Event::reset()
{
    set_current(none);
    for(auto& section : _sections) section->reset();
}

////////////////////////////////////////////////////////////////////////////////
void Event::set_current(int current)
{
    _current = current;
    emit current_changed(_current);
}

////////////////////////////////////////////////////////////////////////////////
void Event::insert(Sections::const_iterator ri, Section::Pointer section)
{
    ri = _sections.insert(ri, std::move(section));
    emit section_inserted(ri - begin());
}

////////////////////////////////////////////////////////////////////////////////
void Event::erase(Sections::const_iterator ri)
{
    ri = _sections.erase(ri);
    emit section_erased(ri - begin());
}

////////////////////////////////////////////////////////////////////////////////
Event::Pointer Event::instance()
{
    static Event::Pointer event(new Event());
    return event;
}
