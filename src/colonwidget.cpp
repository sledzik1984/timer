////////////////////////////////////////////////////////////////////////////////
#include "colonwidget.hpp"

#include <QByteArray>
#include <QRect>

////////////////////////////////////////////////////////////////////////////////
static const QRect viewbox = { 0, 0, 190, 790 };
static const QByteArray contents = R"(<circle cx="95" cy="240" r="35"/><circle cx="95" cy="550" r="35"/>)";

////////////////////////////////////////////////////////////////////////////////
ColonWidget::ColonWidget(QColor color, QWidget* parent) :
    SvgWidget(::viewbox, std::move(color), ::contents, parent),
    PressWidget(this)
{ }

////////////////////////////////////////////////////////////////////////////////
void ColonWidget::resizeEvent(QResizeEvent*)
{
    if(viewbox().isValid())
    {
        auto width = height() * viewbox().width() / viewbox().height();
        setMinimumWidth(width);
        setMaximumWidth(width);
    }
    else
    {
        setMinimumWidth(0);
        setMaximumWidth(QWIDGETSIZE_MAX);
    }
}
