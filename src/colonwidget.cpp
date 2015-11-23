////////////////////////////////////////////////////////////////////////////////
#include "colonwidget.hpp"
#include <QByteArray>

////////////////////////////////////////////////////////////////////////////////
ColonWidget::ColonWidget(QColor color, QWidget* parent) :
    SvgWidget(parent)
{
    set_color(std::move(color));
    reload();

    connect(this, &ColonWidget::color_changed, this, &ColonWidget::reload);
}

////////////////////////////////////////////////////////////////////////////////
void ColonWidget::set_color(QColor color)
{
    if(color != _color)
    {
        _color = std::move(color);
        emit color_changed(_color);
    }
}

////////////////////////////////////////////////////////////////////////////////
void ColonWidget::reload()
{
    if(!_frozen)
    {
        QByteArray contents = "<svg viewBox=\"0 0 190 790\" fill=\"%color%\"><circle cx=\"95\" cy=\"240\" r=\"35\"/><circle cx=\"95\" cy=\"550\" r=\"35\"/></svg>";
        contents.replace("%color%", _color.name().toLatin1());
        load(contents);
    }
}
