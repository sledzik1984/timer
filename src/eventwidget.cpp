////////////////////////////////////////////////////////////////////////////////
#include "clock.hpp"
#include "event.hpp"
#include "eventwidget.hpp"

////////////////////////////////////////////////////////////////////////////////
EventWidget::EventWidget(QColor color, QWidget* parent) :
    TimeWidget(QTime(0, 0), std::move(color), parent)
{
    connect(&Clock::instance(), &Clock::datetime_changed, this, &EventWidget::update);
}

////////////////////////////////////////////////////////////////////////////////
void EventWidget::update()
{
    QTime time(0, 0);

    if(Event::instance().is_started())
        time = time.addSecs(Event::instance().started().secsTo(Clock::instance().datetime()));
    set_time(time);
}
