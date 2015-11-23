////////////////////////////////////////////////////////////////////////////////
#include "periodwidget.hpp"
#include <QByteArray>

////////////////////////////////////////////////////////////////////////////////
PeriodWidget::PeriodWidget(QColor color, QWidget* parent) :
    SvgWidget(parent)
{
    set_color(std::move(color));
    reload();

    connect(this, &PeriodWidget::color_changed, this, &PeriodWidget::reload);
}

////////////////////////////////////////////////////////////////////////////////
void PeriodWidget::set_color(QColor color)
{
    if(color != _color)
    {
        _color = std::move(color);
        emit color_changed(_color);
    }
}

////////////////////////////////////////////////////////////////////////////////
void PeriodWidget::reload()
{
    if(!_frozen)
    {
        QByteArray contents = "<svg viewBox=\"0 0 190 790\" fill=\"%color%\"><circle cx=\"95\" cy=\"695\" r=\"35\"/></svg>";
        contents.replace("%color%", _color.name().toLatin1());
        load(contents);
    }
}
