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

    _blink.setInterval(500);
    connect(&_blink, &QTimer::timeout, [this]() { setVisible(!isVisible()); });

    _stop.setInterval(10000);
    connect(&_stop, &QTimer::timeout, this, &CountDownWidget::reset);
}

////////////////////////////////////////////////////////////////////////////////
void CountDownWidget::reset()
{
    _stop.stop();

    set_time(midnight);
    emit time_reset();
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
    if(time > _threshold)
    {
        _blink.stop();
        set_color(Qt::green);
        show();
    }
    else if(time > midnight)
    {
        set_color(Qt::red);
        if(!_blink.isActive()) _blink.start();
    }
    else
    {
        _blink.stop();
        set_color(Qt::gray);
        show();
    }

    _stop.start();
}
