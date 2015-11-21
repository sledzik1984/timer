////////////////////////////////////////////////////////////////////////////////
#include "error.hpp"
#include "section.hpp"

////////////////////////////////////////////////////////////////////////////////
Section::Section(QString name, Seconds duration)
{
    set_name(std::move(name));
    set_duration(std::move(duration));
    reset();
}

////////////////////////////////////////////////////////////////////////////////
void Section::start()
{
    if(!is_started()) _started = Clock::instance().datetime();
}

////////////////////////////////////////////////////////////////////////////////
void Section::end()
{
    if(is_started() && !is_ended()) _ended = Clock::instance().datetime();
}

////////////////////////////////////////////////////////////////////////////////
Seconds Section::overage() const
{
    if(is_started())
    {
        QDateTime end = started().addSecs(duration());
        if(!is_ended())
        {
            int overage = end.secsTo(Clock::instance().datetime());
            if(overage > 0) return overage;
        }
        else return end.secsTo(ended());
    }

    return 0;
}
