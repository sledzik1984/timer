#ifndef PERIODWIDGET_HPP
#define PERIODWIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include "svgwidget.hpp"

#include <QColor>
#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
class PeriodWidget : public SvgWidget
{
    Q_OBJECT

public:
    ////////////////////
    explicit PeriodWidget(QWidget* parent = nullptr);
    explicit PeriodWidget(QColor color, QWidget* parent = nullptr);

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
#endif // PERIODWIDGET_HPP
