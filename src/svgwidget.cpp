////////////////////////////////////////////////////////////////////////////////
#include "svgwidget.hpp"

////////////////////////////////////////////////////////////////////////////////
SvgWidget::SvgWidget(QWidget* parent) :
    QSvgWidget(parent)
{
    _long.setSingleShot(true);
    _long.setInterval(1000);
    connect(&_long, &QTimer::timeout, this, &SvgWidget::long_pressed);
}

////////////////////////////////////////////////////////////////////////////////
void SvgWidget::mousePressEvent(QMouseEvent* event)
{
    QSvgWidget::mousePressEvent(event);

    if(!event->isAccepted())
    {
        _long.start();
        emit pressed();

        event->accept();
    }
}

////////////////////////////////////////////////////////////////////////////////
void SvgWidget::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);

    if(!event->isAccepted())
    {
        if(_long.isActive())
        {
            _long.stop();
            emit clicked();
        }

        emit released();
        event->accept();
    }
}
