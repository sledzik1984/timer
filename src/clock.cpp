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
void Clock::swap(Clock& c)
{
    std::swap(_offset, c._offset);
    std::swap(_datetime, c._datetime);
}

////////////////////////////////////////////////////////////////////////////////
void Clock::update()
{
    QDateTime current = QDateTime::currentDateTime().addSecs(offset());

    // remove milliseconds
    current = QDateTime(current.date(), QTime::fromMSecsSinceStartOfDay((current.time().msecsSinceStartOfDay() / 1000) * 1000));

    if(current != _datetime)
    {
        _datetime = std::move(current);
        emit datetime_changed(_datetime);
    }
}

////////////////////////////////////////////////////////////////////////////////
Clock& Clock::instance()
{
    static Clock clock;
    return clock;
}
