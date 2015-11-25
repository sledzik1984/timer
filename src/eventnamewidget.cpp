////////////////////////////////////////////////////////////////////////////////
#include "event.hpp"
#include "eventnamewidget.hpp"

////////////////////////////////////////////////////////////////////////////////
EventNameWidget::EventNameWidget(QWidget* parent) :
    QWidget(parent)
{
    setupUi(this);

    connect(&*Event::instance(), &Event::name_changed, this, &EventNameWidget::set_name);
    connect(&*Event::instance(), &Event::date_changed, this, &EventNameWidget::set_date);
}

////////////////////////////////////////////////////////////////////////////////
void EventNameWidget::set_name(const QString& _name)
{
    name->setText(_name);
}

////////////////////////////////////////////////////////////////////////////////
void EventNameWidget::set_date(const QDate& _date)
{
    date->setText(_date.toString("ddd, MMM d, yyyy"));
}
