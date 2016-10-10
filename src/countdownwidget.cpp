////////////////////////////////////////////////////////////////////////////////
#include "countdownwidget.hpp"

////////////////////////////////////////////////////////////////////////////////
const QTime midnight { 0, 0 };

////////////////////////////////////////////////////////////////////////////////
CountDownWidget::CountDownWidget(QWidget* parent) :
    TimeWidget(Display::HrsMinSec, Qt::gray, parent),
    _threshold(midnight)
{
    reset();

    connect(this, &CountDownWidget::long_pressed, this, &CountDownWidget::reset);
    connect(this, &CountDownWidget::time_changed, this, &CountDownWidget::update);

    _timer.setInterval(500);
    connect(&_timer, &QTimer::timeout, [this]() { setVisible(!isVisible()); });
}

////////////////////////////////////////////////////////////////////////////////
void CountDownWidget::reset()
{
    set_time(midnight);
}

////////////////////////////////////////////////////////////////////////////////
void CountDownWidget::set_threshold(QTime threshold)
{
    _threshold = std::move(threshold);
    update(time());
}

////////////////////////////////////////////////////////////////////////////////
void CountDownWidget::update(const QTime& time)
{
    if(time <= _threshold && time != midnight)
    {
        set_color(Qt::red);
        if(!_timer.isActive()) _timer.start();
    }
    else
    {
        set_color(Qt::gray);
        _timer.stop();
        show();
    }
}
