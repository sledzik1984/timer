////////////////////////////////////////////////////////////////////////////////
#include "eventtimewidget.hpp"
#include "mainwindow.hpp"
#include "trucktimewidget.hpp"
#include "videotimewidget.hpp"

////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    setupUi(this);

    panel_1->layout()->addWidget(new TruckTimeWidget());
    panel_2->layout()->addWidget(new EventTimeWidget());
    panel_3->layout()->addWidget(new VideoTimeWidget());
}
