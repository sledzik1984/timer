////////////////////////////////////////////////////////////////////////////////
#include "svgwidget.hpp"
#include <QSizePolicy>

////////////////////////////////////////////////////////////////////////////////
SvgWidget::SvgWidget(QWidget* parent) :
    QSvgWidget(parent)
{
    ////////////////////
    QSizePolicy policy(sizePolicy());

    policy.setHeightForWidth(true);
    setSizePolicy(policy);

    ////////////////////
    _long_press.setSingleShot(true);
    _long_press.setInterval(1000);
    connect(&_long_press, &QTimer::timeout, this, &SvgWidget::long_pressed);
}

////////////////////////////////////////////////////////////////////////////////
int SvgWidget::heightForWidth(int width) const
{
    return width * sizeHint().height() / sizeHint().width();
}

////////////////////////////////////////////////////////////////////////////////
void SvgWidget::mousePressEvent(QMouseEvent* event)
{
    QSvgWidget::mousePressEvent(event);

    if(!event->isAccepted())
    {
        _long_press.start();
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
        if(_long_press.isActive())
        {
            _long_press.stop();
            emit clicked();
        }

        emit released();
        event->accept();
    }
}
