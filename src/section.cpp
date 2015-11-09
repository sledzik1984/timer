////////////////////////////////////////////////////////////////////////////////
#include "section.hpp"
#include <stdexcept>

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
    if(!is_started()) _started = Clock::now();
}

////////////////////////////////////////////////////////////////////////////////
void Section::end()
{
    if(is_started() && !is_ended()) _ended = Clock::now();
}

////////////////////////////////////////////////////////////////////////////////
Section::Duration Section::overage() const
{
    return is_started() ? std::chrono::duration_cast<Duration>(
                              (started() + duration()) - (is_ended() ? ended() : Clock::now())
                          )
                        : Duration(0);
}
