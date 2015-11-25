////////////////////////////////////////////////////////////////////////////////
#include "event.hpp"
#include "eventtitlewidget.hpp"

////////////////////////////////////////////////////////////////////////////////
EventTitleWidget::EventTitleWidget(QWidget* parent) :
    QWidget(parent)
{
    setupUi(this);

    connect(&*Event::instance(), &Event::name_changed, this, &EventTitleWidget::set_name);
    connect(&*Event::instance(), &Event::date_changed, this, &EventTitleWidget::set_date);
}

////////////////////////////////////////////////////////////////////////////////
void EventTitleWidget::set_name(const QString& _name)
{
    name->setText(_name);
}

////////////////////////////////////////////////////////////////////////////////
void EventTitleWidget::set_date(const QDate& _date)
{
    date->setText(_date.toString("ddd, MMM d, yyyy"));
}
