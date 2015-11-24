////////////////////////////////////////////////////////////////////////////////
#include "error.hpp"
#include "section.hpp"

////////////////////////////////////////////////////////////////////////////////
Section::Section(QString name, Seconds duration)
{
    set_name(std::move(name));
    set_duration(std::move(duration));
}

////////////////////////////////////////////////////////////////////////////////
void Section::swap(Section& s)
{
    set_name    (std::move(s._name    ));
    set_duration(std::move(s._duration));
    set_started (std::move(s._started ));
    set_ended   (std::move(s._ended   ));
}

////////////////////////////////////////////////////////////////////////////////
void Section::set_name(QString name)
{
    if(name != _name)
    {
        _name = std::move(name);
        emit name_changed(_name);
    }
}

////////////////////////////////////////////////////////////////////////////////
void Section::set_duration(Seconds duration)
{
    if(duration != _duration)
    {
        _duration = std::move(duration);
        emit duration_changed(_duration);
    }
}

////////////////////////////////////////////////////////////////////////////////
void Section::start()
{
    if(!is_started()) set_started(Clock::instance().datetime());
}

////////////////////////////////////////////////////////////////////////////////
void Section::end()
{
    if(is_started() && !is_ended()) set_ended(Clock::instance().datetime());
}

////////////////////////////////////////////////////////////////////////////////
void Section::reset()
{
    set_ended(QDateTime());
    set_started(QDateTime());
}

////////////////////////////////////////////////////////////////////////////////
Seconds Section::overage() const
{
    if(is_started())
    {
        auto end = started().addSecs(duration());
        if(!is_ended())
        {
            int overage = end.secsTo(Clock::instance().datetime());
            if(overage > 0) return overage;
        }
        else return end.secsTo(ended());
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
void Section::set_started(QDateTime started)
{
    if(started != _started)
    {
        _started = std::move(started);
        emit started_changed(_started);
    }
}

////////////////////////////////////////////////////////////////////////////////
void Section::set_ended(QDateTime ended)
{
    if(ended != _ended)
    {
        _ended = std::move(ended);
        emit ended_changed(_ended);
    }
}
