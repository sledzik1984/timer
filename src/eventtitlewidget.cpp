////////////////////////////////////////////////////////////////////////////////
#include "event.hpp"
#include "eventtitlewidget.hpp"

////////////////////////////////////////////////////////////////////////////////
EventTitleWidget::EventTitleWidget(QWidget* parent) :
    QWidget(parent)
{
    setupUi(this);

    name->setText(Event::instance().name());
    date->setText(Event::instance().date().toString("ddd, MMM d, yyyy"));
}
