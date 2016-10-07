////////////////////////////////////////////////////////////////////////////////
#include "countdownwidget.hpp"
#include "oscsource.hpp"
#include "videotimewidget.hpp"

////////////////////////////////////////////////////////////////////////////////
VideoTimeWidget::VideoTimeWidget(QWidget* parent) :
    StyleWidget(parent)
{
    setupUi(this);

    auto widget = new CountDownWidget(Qt::gray, Qt::red, QTime(0, 0, 15), this);
    layout()->addWidget(widget);

    connect(&*OscSource::instance(), &OscSource::time_changed, [widget](const QTime& time, const QTime& total)
    {
        widget->set_time(QTime(0, 0, 0).addMSecs(time.msecsTo(total)));
    });
    connect(&*OscSource::instance(), &OscSource::status_changed, [widget](Status status) { if(status == Reset) widget->reset(); });
}
