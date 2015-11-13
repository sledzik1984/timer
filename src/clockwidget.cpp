////////////////////////////////////////////////////////////////////////////////
#include "clockwidget.hpp"

////////////////////////////////////////////////////////////////////////////////
ClockWidget::ClockWidget(QColor color, QWidget* parent) :
    TimeWidget(QTime(0, 0), std::move(color), parent)
{
    connect(this, &ClockWidget::hours_clicked       , [this](){ add_offset(3600); });
    connect(this, &ClockWidget::hours_long_pressed  , [this](){ set_offset(   0); });

    connect(this, &ClockWidget::minutes_clicked     , [this](){ add_offset(  60); });
    connect(this, &ClockWidget::minutes_long_pressed, [this](){ set_offset(   0); });

    connect(this, &ClockWidget::seconds_clicked     , [this](){ add_offset(   1); });
    connect(this, &ClockWidget::seconds_long_pressed, [this](){ set_offset(   0); });

    connect(&_update, &QTimer::timeout, this, &ClockWidget::update);

    _update.setInterval(100);
    _update.start();
}

////////////////////////////////////////////////////////////////////////////////
void ClockWidget::update()
{
    set_time(QTime::currentTime().addSecs(_offset));
}

////////////////////////////////////////////////////////////////////////////////
void ClockWidget::add_offset(int amount)
{
    switch(location())
    {
    case Location::top:
        _offset += amount;
        break;

    case Location::bottom:
        _offset -= amount;
        break;

    default: break;
    }
}
