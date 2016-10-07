////////////////////////////////////////////////////////////////////////////////
#include "countdownwidget.hpp"

////////////////////////////////////////////////////////////////////////////////
CountDownWidget::CountDownWidget(QColor color, QColor color_lo, QTime time_lo, QWidget* parent) :
    TimeWidget(Display::HrsMinSec, color, parent),
    _color(std::move(color)),
    _color_lo(std::move(color_lo)),
    _time_lo(std::move(time_lo))
{
    reset();

    connect(this, &CountDownWidget::long_pressed, this, &CountDownWidget::reset);
    connect(this, &CountDownWidget::time_changed, this, &CountDownWidget::update);
}

////////////////////////////////////////////////////////////////////////////////
void CountDownWidget::reset()
{
    set_time(QTime(0, 0, 0));
}

////////////////////////////////////////////////////////////////////////////////
void CountDownWidget::update(const QTime& time)
{
    set_color(time > _time_lo || time == QTime(0, 0, 0) ? _color : _color_lo);
}
