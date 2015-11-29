////////////////////////////////////////////////////////////////////////////////
#include "stylewidget.hpp"

#include <QPainter>
#include <QStyle>
#include <QStyleOption>

////////////////////////////////////////////////////////////////////////////////
void StyleWidget::paintEvent(QPaintEvent*)
{
    QStyleOption option;
    option.initFrom(this);

    QPainter painter(this);

    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}
