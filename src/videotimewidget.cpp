////////////////////////////////////////////////////////////////////////////////
#include "videotimewidget.hpp"

////////////////////////////////////////////////////////////////////////////////
VideoTimeWidget::VideoTimeWidget(QWidget* parent) :
    TimeWidget(Display::HrsMinSec, Qt::gray, parent),
    _time_lo(0, 0, 0),
    _video(1, 10)
{
    reset();

    connect(this, &VideoTimeWidget::long_pressed, this, &VideoTimeWidget::reset);

    connect(&_video, &Osc::Video::time_changed, this, &VideoTimeWidget::update);
    connect(&_event, &Osc::Event::status_changed, [this](Osc::Event::Status status){ if(status == Osc::Event::Reset) reset(); });

    _timer.setInterval(500);
    connect(&_timer, &QTimer::timeout, [this]() { setVisible(!isVisible()); });
}

////////////////////////////////////////////////////////////////////////////////
void VideoTimeWidget::reset()
{
    update(QTime(0, 0, 0), QTime(0, 0, 0));
}

////////////////////////////////////////////////////////////////////////////////
void VideoTimeWidget::update(const QTime& time, const QTime& total)
{
    auto remain = QTime(0, 0, 0).addMSecs(time.msecsTo(total));

    if(remain <= _time_lo && remain != QTime(0,0,0))
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

    set_time(remain);
}
