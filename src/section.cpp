////////////////////////////////////////////////////////////////////////////////
#include "error.hpp"
#include "section.hpp"

#include <QTime>

////////////////////////////////////////////////////////////////////////////////
Section::Section(QString name, Section::Duration duration)
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
Section::Duration Section::overage() const
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

////////////////////////////////////////////////////////////////////////////////
QString Section::to_string(const Duration& duration)
{
    return QTime(0, 0).addSecs(duration).toString("H:mm:ss");
}

////////////////////////////////////////////////////////////////////////////////
QString Section::to_string(const QDateTime& datetime)
{
    return datetime.toString("MMM d h:mm:ss yyyy");
}

////////////////////////////////////////////////////////////////////////////////
Section::Duration Section::to_duration(const QString& string)
{
    return QTime(0, 0).secsTo(QTime::fromString(string, "H:mm:ss"));
}

////////////////////////////////////////////////////////////////////////////////
QDateTime Section::to_datetime(const QString& string)
{
    return QDateTime::fromString("MMM d h:mm:ss yyyy");
}
