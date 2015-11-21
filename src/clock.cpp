////////////////////////////////////////////////////////////////////////////////
#include "clock.hpp"

////////////////////////////////////////////////////////////////////////////////
Clock::Clock(QObject* parent) :
    QObject(parent)
{
    connect(&_update, &QTimer::timeout, this, &Clock::update);

    _update.setInterval(100);
    _update.start();
}

////////////////////////////////////////////////////////////////////////////////
void Clock::set_offset(Seconds seconds)
{
    if(seconds != offset())
    {
        _offset = std::move(seconds);
        emit offset_changed(offset());
    }
}

////////////////////////////////////////////////////////////////////////////////
void Clock::add_offset(Seconds seconds)
{
    set_offset(offset() + std::move(seconds));
}

////////////////////////////////////////////////////////////////////////////////
void Clock::update()
{
    QDateTime current = QDateTime::currentDateTime().addSecs(offset());

    // remove milliseconds
    current = QDateTime(current.date(), QTime::fromMSecsSinceStartOfDay((current.time().msecsSinceStartOfDay() / 1000) * 1000));

    if(current != datetime())
    {
        _datetime = std::move(current);
        emit datetime_changed(datetime());
    }
}

////////////////////////////////////////////////////////////////////////////////
Clock& Clock::instance()
{
    static Clock clock;
    return clock;
}
