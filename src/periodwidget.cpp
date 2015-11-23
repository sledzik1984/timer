////////////////////////////////////////////////////////////////////////////////
#include "periodwidget.hpp"
#include <QByteArray>

////////////////////////////////////////////////////////////////////////////////
PeriodWidget::PeriodWidget(QWidget* parent) :
    PeriodWidget(QColor(), parent)
{ }

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
    QByteArray contents = "<svg viewBox=\"0 0 190 790\"";
    if(_color.isValid())
        contents += " fill=\"" + _color.name().toLatin1() + "\"><circle cx=\"95\" cy=\"695\" r=\"35\"/";
    contents += "></svg>";
    load(contents);
}
