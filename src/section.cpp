////////////////////////////////////////////////////////////////////////////////
#include "error.hpp"
#include "section.hpp"

#include <ctime>
#include <iomanip>
#include <sstream>


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
    if(!is_started()) _started = Clock::now();
}

////////////////////////////////////////////////////////////////////////////////
void Section::end()
{
    if(is_started() && !is_ended()) _ended = Clock::now();
}

////////////////////////////////////////////////////////////////////////////////
Duration Section::overage() const
{
    if(is_started())
    {
        if(!is_ended())
        {
            Duration overage = std::chrono::duration_cast<Duration>(
                started() + duration() - Clock::now()
            );
            if(overage > Duration(0)) return overage;
        }
        else return std::chrono::duration_cast<Duration>(started() + duration() - ended());
    }

    return Duration(0);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
QString to_string(const Duration& duration)
{
    std::time_t time = Clock::to_time_t(Timepoint(duration));

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%X");

    return ss.str().data();
}

////////////////////////////////////////////////////////////////////////////////
QString to_string(const Timepoint& timepoint)
{
    std::time_t time = Clock::to_time_t(timepoint);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%c");

    return ss.str().data();
}

////////////////////////////////////////////////////////////////////////////////
Duration to_duration(const QString& string)
{
    std::tm tm { };

    std::stringstream ss(string.toLatin1().data());
    ss >> std::get_time(&tm, "%X");

    if(ss.fail()) throw FormatError("Invalid duration format");

    using namespace std::chrono;
    return hours(tm.tm_hour) + minutes(tm.tm_min) + seconds(tm.tm_sec);
}

////////////////////////////////////////////////////////////////////////////////
Timepoint to_timepoint(const QString& string)
{
    std::tm tm { };

    std::stringstream ss(string.toLatin1().data());
    ss >> std::get_time(&tm, "%c");

    if(ss.fail()) throw FormatError("Invalid date/time format");

    return Clock::from_time_t(std::mktime(&tm));
}
