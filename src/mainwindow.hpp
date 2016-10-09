////////////////////////////////////////////////////////////////////////////////
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

////////////////////////////////////////////////////////////////////////////////
#include "clockwidget.hpp"
#include "eventtimewidget.hpp"
#include "ui_mainwindow.h"
#include "videotimewidget.hpp"

////////////////////////////////////////////////////////////////////////////////
enum class Panel { TruckTime, EventTime, VideoTime };

////////////////////////////////////////////////////////////////////////////////
class MainWindow : public QWidget, private Ui::MainWindow
{
    Q_OBJECT

public:
    ////////////////////
    explicit MainWindow(QWidget* parent = nullptr);

    ////////////////////
    void show_panel(Panel p) { set_panel_visible(p, true); }
    void hide_panel(Panel p) { set_panel_visible(p, false); }

    void set_panel_visible(Panel p, bool visible) { panel(p)->setVisible(visible); }

    void set_time_lo(QTime time) { _video->set_time_lo(std::move(time)); }

private:
    QWidget* panel(Panel) const;

    VideoTimeWidget* _video;
};

////////////////////////////////////////////////////////////////////////////////
#endif // MAINWINDOW_HPP
