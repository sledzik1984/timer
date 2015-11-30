////////////////////////////////////////////////////////////////////////////////
#include "timelinewidget.hpp"

////////////////////////////////////////////////////////////////////////////////
TimelineWidget::TimelineWidget(QWidget* parent) :
    QWidget(parent),
    _layout(new QHBoxLayout(this))
{
    _layout->setContentsMargins(0, 0, 0, 0);
}
