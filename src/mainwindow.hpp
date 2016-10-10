////////////////////////////////////////////////////////////////////////////////
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

////////////////////////////////////////////////////////////////////////////////
#include "clockwidget.hpp"
#include "countdownwidget.hpp"
#include "osc_event.hpp"
#include "osc_video.hpp"
#include "timerwidget.hpp"
#include "ui_mainwindow.h"

#include <QString>
#include <QTime>
#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    ////////////////////
    explicit MainWindow(QWidget* parent = nullptr);

    void set_threshold(QTime threshold) { _count->set_threshold(std::move(threshold)); }

private:
    ////////////////////
    ClockWidget* _clock;
    TimerWidget* _timer;
    CountDownWidget* _count;

    Osc::Event _event;
    Osc::Video _video;

    void set_video_name(QString);
    void reset_video_name() { set_video_name("CURRENT VIDEO"); }
};

////////////////////////////////////////////////////////////////////////////////
#endif // MAINWINDOW_HPP
