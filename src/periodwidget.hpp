////////////////////////////////////////////////////////////////////////////////
#ifndef PERIODWIDGET_HPP
#define PERIODWIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include "presswidget.hpp"
#include "svgwidget.hpp"

#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
class PeriodWidget : public SvgWidget, public PressWidget
{
    Q_OBJECT

public:
    ////////////////////
    explicit PeriodWidget(QWidget* parent = nullptr) : PeriodWidget(QColor(), parent) { }
    explicit PeriodWidget(QColor color, QWidget* parent = nullptr);

    using SvgWidget::set_color; // make SvgWidget::set_color public

signals:
    ////////////////////
    void clicked();
    void pressed();
    void long_pressed();
    void released();
};

////////////////////////////////////////////////////////////////////////////////
#endif // PERIODWIDGET_HPP
