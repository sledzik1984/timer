////////////////////////////////////////////////////////////////////////////////
#ifndef VIDEOTIMEWIDGET_HPP
#define VIDEOTIMEWIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include "osc_event.hpp"
#include "osc_video.hpp"
#include "timewidget.hpp"

#include <QTime>
#include <QTimer>

#include <utility>

////////////////////////////////////////////////////////////////////////////////
class VideoTimeWidget : public TimeWidget
{
    Q_OBJECT

public:
    ////////////////////
    explicit VideoTimeWidget(QWidget* parent = nullptr);

    void reset();
    void set_time_lo(QTime time) { _time_lo = std::move(time); }

private:
    ////////////////////
    void update(const QTime& time, const QTime& total);

    QTime _time_lo;
    QTimer _timer;

    Osc::Event _event;
    Osc::Video _video;
};

////////////////////////////////////////////////////////////////////////////////
#endif // VIDEOTIMEWIDGET_HPP
