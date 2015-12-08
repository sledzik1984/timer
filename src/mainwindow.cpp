////////////////////////////////////////////////////////////////////////////////
#include "eventnamewidget.hpp"
#include "mainwindow.hpp"
#include "trucktimewidget.hpp"

////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    setupUi(this);

    panel_0->layout()->addWidget(new EventNameWidget());
    panel_1->layout()->addWidget(new TruckTimeWidget());
}
