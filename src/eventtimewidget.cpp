////////////////////////////////////////////////////////////////////////////////
#include "clock.hpp"
#include "eventtimewidget.hpp"

////////////////////////////////////////////////////////////////////////////////
EventTimeWidget::EventTimeWidget(QWidget* parent) :
    TimeWidget(Display::HrsMinSec, Qt::gray, parent)
{
    reset();

    connect(this, &EventTimeWidget::clicked, this, &EventTimeWidget::proc_clicked);
    connect(this, &EventTimeWidget::long_pressed, this, &EventTimeWidget::reset);

    connect(&*Clock::instance(), &Clock::datetime_changed, this, &EventTimeWidget::update);

    connect(&_event, &Osc::Event::status_changed, [this](Osc::Event::Status status)
    {
        switch(status)
        {
        case Osc::Event::Started: start(); break;
        case Osc::Event::Stopped: stop() ; break;
        case Osc::Event::Reset  : reset(); break;
        }
    });
}

////////////////////////////////////////////////////////////////////////////////
void EventTimeWidget::start()
{
    _epoch = Clock::instance()->datetime().toMSecsSinceEpoch();
    _running = true;
}

////////////////////////////////////////////////////////////////////////////////
void EventTimeWidget::reset()
{
    stop();
    set_time(QTime(0, 0, 0));
}

////////////////////////////////////////////////////////////////////////////////
void EventTimeWidget::proc_clicked(Unit unit)
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
void EventTimeWidget::update(const QDateTime& datetime)
{
    if(_running) set_time(QTime(0, 0, 0).addMSecs(datetime.toMSecsSinceEpoch() - _epoch));
}
