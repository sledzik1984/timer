////////////////////////////////////////////////////////////////////////////////
#include "clockwidget.hpp"
#include "trucktimewidget.hpp"

////////////////////////////////////////////////////////////////////////////////
TruckTimeWidget::TruckTimeWidget(QWidget* parent) :
    QWidget(parent)
{
    setupUi(this);

    layout()->addWidget(new ClockWidget(Qt::red));
}
