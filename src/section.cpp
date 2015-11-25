////////////////////////////////////////////////////////////////////////////////
#include "error.hpp"
#include "section.hpp"

////////////////////////////////////////////////////////////////////////////////
Section::Section(QString name, Seconds period)
{
    set_name(std::move(name));
    set_period(std::move(period));
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
void Section::set_period(Seconds period)
{
    if(period != _period)
    {
        _period = std::move(period);
        emit period_changed(_period);
    }
}

////////////////////////////////////////////////////////////////////////////////
QDateTime Section::ending() const
{
    QDateTime value = started();
    if(value.isValid()) value = value.addSecs(period());

    return value;
}

////////////////////////////////////////////////////////////////////////////////
Seconds Section::real_period() const
{
    QDateTime start = started();
    if(start.isValid())
    {
        QDateTime end = ended();
        if(end.isValid()) return start.secsTo(end);
    }

    return period();
}

////////////////////////////////////////////////////////////////////////////////
Seconds Section::passed() const
{
    QDateTime start = started();
    if(start.isValid())
    {
        QDateTime end = ended();
        if(!end.isValid()) end = Clock::instance()->datetime();

        return start.secsTo(end);
    }
    else return 0;
}

////////////////////////////////////////////////////////////////////////////////
Seconds Section::remain() const
{
    Seconds seconds = real_period() - passed();
    if(seconds < 0) seconds = 0;

    return seconds;
}

////////////////////////////////////////////////////////////////////////////////
Seconds Section::overage() const
{
    Seconds seconds = passed() - period();
    if(!ended().isValid() && seconds < 0) seconds = 0;

    return seconds;
}

////////////////////////////////////////////////////////////////////////////////
void Section::start()
{
    if(!started().isValid()) set_started(Clock::instance()->datetime());
}

////////////////////////////////////////////////////////////////////////////////
void Section::end()
{
    if(started().isValid() && !ended().isValid()) set_ended(Clock::instance()->datetime());
}

////////////////////////////////////////////////////////////////////////////////
void Section::reset()
{
    set_ended(QDateTime());
    set_started(QDateTime());
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
