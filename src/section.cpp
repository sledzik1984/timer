////////////////////////////////////////////////////////////////////////////////
#include "error.hpp"
#include "section.hpp"

////////////////////////////////////////////////////////////////////////////////
Section::Section(QString name, Duration duration)
{
    set_name(std::move(name));
    set_duration(std::move(duration));
    reset();
}

////////////////////////////////////////////////////////////////////////////////
void Section::start()
{
    if(!is_started()) _started = QDateTime::currentDateTime();
}

////////////////////////////////////////////////////////////////////////////////
void Section::end()
{
    if(is_started() && !is_ended()) _ended = QDateTime::currentDateTime();
}

////////////////////////////////////////////////////////////////////////////////
Duration Section::overage() const
{
    if(is_started())
    {
        QDateTime end = started().addSecs(duration());
        if(!is_ended())
        {
            int overage = end.secsTo(QDateTime::currentDateTime());
            if(overage > 0) return overage;
        }
        else return end.secsTo(ended());
    }

    return 0;
}
