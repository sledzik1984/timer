////////////////////////////////////////////////////////////////////////////////
#include "countupwidget.hpp"
#include "eventtimewidget.hpp"
#include "oscsource.hpp"

////////////////////////////////////////////////////////////////////////////////
EventTimeWidget::EventTimeWidget(QWidget* parent) :
    StyleWidget(parent)
{
    setupUi(this);

    auto widget = new CountUpWidget(Qt::gray, this);
    layout()->addWidget(widget);

    connect(&*OscSource::instance(), &OscSource::status_changed, [widget](Status status)
    {
        switch(status)
        {
        case Start: widget->start(); break;
        case Stop : widget->stop() ; break;
        case Reset: widget->reset(); break;
        }
    });
}
