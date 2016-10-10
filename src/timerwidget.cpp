////////////////////////////////////////////////////////////////////////////////
#include "clock.hpp"
#include "timerwidget.hpp"

////////////////////////////////////////////////////////////////////////////////
const QTime midnight { 0, 0 };

////////////////////////////////////////////////////////////////////////////////
TimerWidget::TimerWidget(QWidget* parent) :
    TimeWidget(Display::HrsMinSec, Qt::gray, parent)
{
    reset();

    connect(this, &TimerWidget::clicked, this, &TimerWidget::proc_clicked);
    connect(this, &TimerWidget::long_pressed, this, &TimerWidget::reset);

    connect(&*Clock::instance(), &Clock::datetime_changed, this, &TimerWidget::update);
}

////////////////////////////////////////////////////////////////////////////////
void TimerWidget::start()
{
    _epoch = Clock::instance()->datetime().addMSecs(-time().msecsSinceStartOfDay()).toMSecsSinceEpoch();
    _running = true;
}

////////////////////////////////////////////////////////////////////////////////
void TimerWidget::reset()
{
    stop();
    set_time(midnight);
}

////////////////////////////////////////////////////////////////////////////////
void TimerWidget::proc_clicked(Unit unit)
{
    qint64 ms = 0;
    switch(unit)
    {
    case Unit::Hours  : ms = 3600000; break;
    case Unit::Minutes: ms =   60000; break;
    case Unit::Seconds: ms =    1000; break;
    }

    switch(location())
    {
    case Location::top:
        _epoch -= ms;
        update(Clock::instance()->datetime());
        break;

    case Location::middle:
        if(!_running) start(); else stop();
        break;

    case Location::bottom:
        _epoch += ms;
        update(Clock::instance()->datetime());
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////
void TimerWidget::update(const QDateTime& datetime)
{
    if(_running) set_time(midnight.addMSecs(datetime.toMSecsSinceEpoch() - _epoch));
}
