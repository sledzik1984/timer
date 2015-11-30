////////////////////////////////////////////////////////////////////////////////
#include "error.hpp"
#include "presswidget.hpp"

////////////////////////////////////////////////////////////////////////////////
PressWidget::PressWidget(QObject* self)
{
    // adopt Monitor as our child object
    new Monitor(self, this);
}

////////////////////////////////////////////////////////////////////////////////
Monitor::Monitor(QObject* parent, PressWidget* widget) :
    QObject(parent), _widget(widget)
{
    parent->installEventFilter(this);

    _long.setSingleShot(true);
    _long.setInterval(1000);
    connect(&_long, &QTimer::timeout, [this](){ _widget->long_pressed(); });
}

////////////////////////////////////////////////////////////////////////////////
bool Monitor::eventFilter(QObject* object, QEvent* event)
{
    switch(event->type())
    {
    case QEvent::MouseButtonPress:
        _long.start();
        _widget->pressed();

        return true;

    case QEvent::MouseButtonRelease:
        if(_long.isActive())
        {
            _long.stop();
            _widget->clicked();
        }
        _widget->released();

        return true;

    default:
        return QObject::eventFilter(object, event);
    }
}
