////////////////////////////////////////////////////////////////////////////////
#include "event.hpp"
#include "eventnamewidget.hpp"

////////////////////////////////////////////////////////////////////////////////
EventNameWidget::EventNameWidget(QWidget* parent) :
    StyleWidget(parent)
{
    setupUi(this);

    connect(&*Event::instance(), &Event::name_changed, this, &EventNameWidget::set_name);
    connect(&*Event::instance(), &Event::date_changed, this, &EventNameWidget::set_date);
}

////////////////////////////////////////////////////////////////////////////////
void EventNameWidget::set_name(const QString& value)
{
    name->setText(value);
}

////////////////////////////////////////////////////////////////////////////////
void EventNameWidget::set_date(const QDate& value)
{
    date->setText(value.toString("ddd, MMM d, yyyy"));
}
