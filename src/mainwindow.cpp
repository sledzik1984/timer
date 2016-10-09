////////////////////////////////////////////////////////////////////////////////
#include "error.hpp"
#include "mainwindow.hpp"

////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    setupUi(this);

    panel(Panel::TruckTime)->layout()->addWidget(new ClockWidget());
    panel(Panel::EventTime)->layout()->addWidget(new EventTimeWidget());
    panel(Panel::VideoTime)->layout()->addWidget(_video = new VideoTimeWidget());
}

////////////////////////////////////////////////////////////////////////////////
QWidget* MainWindow::panel(Panel panel) const
{
    switch(panel)
    {
    case Panel::TruckTime: return panel_1;
    case Panel::EventTime: return panel_2;
    case Panel::VideoTime: return panel_3;
    }
    throw InvalidError("Invalid panel index");
}
