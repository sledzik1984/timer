////////////////////////////////////////////////////////////////////////////////
#include "error.hpp"
#include "eventtimewidget.hpp"
#include "mainwindow.hpp"
#include "trucktimewidget.hpp"
#include "videotimewidget.hpp"

////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    setupUi(this);

    panel(TruckTime)->layout()->addWidget(new TruckTimeWidget());
    panel(EventTime)->layout()->addWidget(new EventTimeWidget());
    panel(VideoTime)->layout()->addWidget(new VideoTimeWidget());
}

////////////////////////////////////////////////////////////////////////////////
QWidget* MainWindow::panel(Panel panel) const
{
    switch(panel)
    {
    case TruckTime: return panel_1;
    case EventTime: return panel_2;
    case VideoTime: return panel_3;
    }
    throw InvalidError("Invalid panel index");
}
