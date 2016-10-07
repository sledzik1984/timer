////////////////////////////////////////////////////////////////////////////////
#include "clock.hpp"
#include "countupwidget.hpp"

////////////////////////////////////////////////////////////////////////////////
CountUpWidget::CountUpWidget(QColor color, QWidget* parent) :
    TimeWidget(Display::HrsMinSec, std::move(color), parent)
{
    reset();

    connect(this, &CountUpWidget::clicked, this, &CountUpWidget::proc_clicked);
    connect(this, &CountUpWidget::long_pressed, this, &CountUpWidget::reset);

    connect(&*Clock::instance(), &Clock::datetime_changed, this, &CountUpWidget::update);
}

////////////////////////////////////////////////////////////////////////////////
void CountUpWidget::start()
{
    _epoch = Clock::instance()->datetime().toMSecsSinceEpoch();
    _running = true;
}

////////////////////////////////////////////////////////////////////////////////
void CountUpWidget::reset()
{
    stop();
    set_time(QTime(0, 0, 0));
}

////////////////////////////////////////////////////////////////////////////////
void CountUpWidget::proc_clicked(Unit unit)
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
        break;

    case Location::middle:
        if(!_running) start(); else stop();
        break;

    case Location::bottom:
        _epoch += ms;
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////
void CountUpWidget::update(const QDateTime& datetime)
{
    if(_running) set_time(QTime(0, 0, 0).addMSecs(datetime.toMSecsSinceEpoch() - _epoch));
}
