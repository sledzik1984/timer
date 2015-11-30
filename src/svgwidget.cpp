////////////////////////////////////////////////////////////////////////////////
#include "svgwidget.hpp"
#include <QTextStream>

////////////////////////////////////////////////////////////////////////////////
SvgWidget::SvgWidget(QRect viewbox, QColor color, QByteArray contents, QWidget* parent) :
    QSvgWidget(parent)
{
    set_viewbox (std::move(viewbox ));
    set_color   (std::move(color   ));
    set_contents(std::move(contents));

    connect(this, &SvgWidget:: viewbox_changed, this, &SvgWidget::reload);
    connect(this, &SvgWidget::   color_changed, this, &SvgWidget::reload);
    connect(this, &SvgWidget::contents_changed, this, &SvgWidget::reload);
}

////////////////////////////////////////////////////////////////////////////////
void SvgWidget::set_viewbox(QRect viewbox)
{
    if(viewbox != _viewbox)
    {
        _viewbox = std::move(viewbox);
        emit viewbox_changed(_viewbox);
    }
}

////////////////////////////////////////////////////////////////////////////////
void SvgWidget::set_color(QColor color)
{
    if(color != _color)
    {
        _color = std::move(color);
        emit color_changed(_color);
    }
}

////////////////////////////////////////////////////////////////////////////////
void SvgWidget::set_contents(QByteArray contents)
{
    if(contents != _contents)
    {
        _contents = std::move(contents);
        emit contents_changed(_contents);
    }
}

////////////////////////////////////////////////////////////////////////////////
void SvgWidget::reload()
{
    QByteArray data;
    QTextStream stream(&data);

    if(_viewbox.isValid())
    {
        stream << "<svg viewBox=" << '"' << _viewbox.x()     << ' ' << _viewbox.y()
                                  << ' ' << _viewbox.width() << ' ' << _viewbox.height() << '"';

        if(_color.isValid()) stream << " fill=" << '"' << _color.name() << '"';
        stream << '>';

        if(_color.isValid()) stream << _contents;
        stream << "</svg>";
    }

    stream.seek(0); // dump data into byte array

    load(data);
}
