////////////////////////////////////////////////////////////////////////////////
#include "mainwindow.hpp"

////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget* parent) :
    QWidget(parent),
    _video(1, 10)
{
    setupUi(this);

    panel_1->layout()->addWidget(_clock = new ClockWidget());
    panel_2->layout()->addWidget(_timer = new TimerWidget());
    panel_3->layout()->addWidget(_count = new CountDownWidget());

    connect(&_event, &Osc::Event::status_changed, [this](Osc::Event::Status status)
    {
        switch(status)
        {
        case Osc::Event::Started:
            _timer->start();
            break;

        case Osc::Event::Stopped:
            _timer->stop();
            break;

        case Osc::Event::Reset:
            _timer->reset();
            _count->reset();
            break;
        }
    });

    connect(&_video, &Osc::Video::time_changed, [this](const QTime& time, const QTime& total)
    {
        _count->set_time(QTime(0, 0).addMSecs(time.msecsTo(total)));
    });
}
