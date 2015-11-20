////////////////////////////////////////////////////////////////////////////////
#include "clockwidget.hpp"

////////////////////////////////////////////////////////////////////////////////
ClockWidget::ClockWidget(QColor color, QWidget* parent) :
    TimeWidget(QTime(0, 0), std::move(color), parent)
{
    connect(this, &ClockWidget::clicked, this, &ClockWidget::proc_clicked);
    connect(this, &ClockWidget::long_pressed, [this](){ set_offset(0); });

    connect(&_update, &QTimer::timeout, this, &ClockWidget::update);

    _update.setInterval(100);
    _update.start();
}

////////////////////////////////////////////////////////////////////////////////
void ClockWidget::set_offset(int offset)
{
    if(offset != _offset)
    {
        _offset = offset;
        emit offset_changed(_offset);
    }
}

////////////////////////////////////////////////////////////////////////////////
void ClockWidget::proc_clicked(Unit unit)
{
    int value = 0;
    switch(unit)
    {
    case Unit::Hours  : value = 3600; break;
    case Unit::Minutes: value =   60; break;
    case Unit::Seconds: value =    1; break;
    }

    switch(location())
    {
    case Location::top:
        set_offset(offset() + value);
        break;

    case Location::bottom:
        set_offset(offset() - value);
        break;

    case Location::middle:
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////
void ClockWidget::update()
{
    set_time(QTime::currentTime().addSecs(offset()));
}
