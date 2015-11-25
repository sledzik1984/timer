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
    if(is_started() || e->is_started()) throw ProgressError("Event::replace");

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
    return _sections[0];
}

////////////////////////////////////////////////////////////////////////////////
Section::Pointer& Event::section(size_t n)
{
    if(n >= size()) throw RangeError("Event::section");
    return _sections[0];
}

////////////////////////////////////////////////////////////////////////////////
void Event::clear()
{
    if(is_started()) throw ProgressError("Event::clear");

    while(size()) erase(rbegin().base());
}

////////////////////////////////////////////////////////////////////////////////
void Event::insert(size_t n, Section::Pointer section)
{
    if(n > size()) throw RangeError("Event::insert");

    auto ri = begin() + n;
    if(n < size() && (*ri)->is_started()) throw ProgressError("Event::insert");

    insert(ri, std::move(section));
}

////////////////////////////////////////////////////////////////////////////////
void Event::erase(size_t n)
{
    if(n >= size()) throw RangeError("Event::erase");

    auto ri = begin() + n;
    if((*ri)->is_started()) throw ProgressError("Event::erase");

    erase(ri);
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
    if(size())
    {
        auto section = *begin();
        if(!section->is_started())
        {
            section->start();
            emit started_changed(section->started());

            return true;
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////
bool Event::next()
{
    for(auto ri = begin(); ri != end(); ++ri)
    {
        auto section = *ri;
        if(section->is_started() && !section->is_ended())
        {
            section->end();
            if(++ri != end())
            {
                section = *ri;
                section->start();
            }
            else emit ended_changed(section->ended());

            return true;
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////
void Event::reset()
{
    for(auto& section : _sections) section->reset();
}

////////////////////////////////////////////////////////////////////////////////
void Event::insert(Sections::const_iterator ri, Section::Pointer section)
{
    _sections.insert(ri, std::move(section));
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
