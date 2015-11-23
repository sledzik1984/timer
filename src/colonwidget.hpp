////////////////////////////////////////////////////////////////////////////////
#ifndef COLONWIDGET_HPP
#define COLONWIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include "freeze.hpp"
#include "svgwidget.hpp"

#include <QColor>
#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
class ColonWidget : public SvgWidget, public FreezingWidget
{
    Q_OBJECT

public:
    explicit ColonWidget(QWidget* parent = nullptr) : ColonWidget(Qt::black, parent) { }
    explicit ColonWidget(QColor color, QWidget* parent = nullptr);

    ////////////////////
    void set_color(QColor color);
    const QColor& color() const noexcept { return _color; }

    void reload();

signals:
    ////////////////////
    void color_changed(const QColor&);

private:
    ////////////////////
    QColor _color;
};

////////////////////////////////////////////////////////////////////////////////
#endif // COLONWIDGET_HPP
