////////////////////////////////////////////////////////////////////////////////
#include "clock.hpp"
#include "clockwidget.hpp"

////////////////////////////////////////////////////////////////////////////////
ClockWidget::ClockWidget(QColor color, QWidget* parent) :
    TimeWidget(Display::HrsMinSec, std::move(color), parent)
{
    connect(this, &ClockWidget::clicked, this, &ClockWidget::change_offset);
    connect(this, &ClockWidget::long_pressed, [this](){ Clock::instance()->set_offset(0); });

    connect(&*Clock::instance(), &Clock::datetime_changed, this, &ClockWidget::update);
}

////////////////////////////////////////////////////////////////////////////////
void ClockWidget::change_offset(Unit unit)
{
    Seconds seconds = 0;
    switch(unit)
    {
    case Unit::Hours  : seconds = 3600; break;
    case Unit::Minutes: seconds =   60; break;
    case Unit::Seconds: seconds =    1; break;
    }

    switch(location())
    {
    case Location::top:
        Clock::instance()->add_offset( std::move(seconds));
        break;

    case Location::bottom:
        Clock::instance()->add_offset(-std::move(seconds));
        break;

    case Location::middle:
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////
void ClockWidget::update(const QDateTime& datetime)
{
    set_time(datetime.time());
}
