////////////////////////////////////////////////////////////////////////////////
#include "mainwindow.hpp"

////////////////////////////////////////////////////////////////////////////////
const QTime midnight { 0, 0 };

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
            reset_video_name();
            break;
        }
    });

    connect(_count, &CountDownWidget::time_reset, this, &MainWindow::reset_video_name);

    connect(&_video, &Osc::Video::time_changed, [this](const QTime& time, const QTime& total)
    {
        _count->set_time(midnight.addMSecs(time.msecsTo(total)));
    });
    connect(&_video, &Osc::Video::name_changed, this, &MainWindow::set_video_name);
}

////////////////////////////////////////////////////////////////////////////////
void MainWindow::set_video_name(QString name)
{
    auto p = name.lastIndexOf('/');
    if(p >= 0) name.remove(0, p + 1);

    p = name.lastIndexOf('.');
    if(p >= 0) name.remove(p, name.size());

    label_3->setText(name.toUpper());
}
