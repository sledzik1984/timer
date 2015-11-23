////////////////////////////////////////////////////////////////////////////////
#ifndef DIGITWIDGET_HPP
#define DIGITWIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include "freeze.hpp"
#include "svgwidget.hpp"

#include <QColor>
#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
enum class Digit
{
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
    none,
};

////////////////////////////////////////////////////////////////////////////////
class DigitWidget : public SvgWidget, public FreezingWidget
{
    Q_OBJECT

public:
    explicit DigitWidget(QWidget* parent = nullptr);
    DigitWidget(Digit digit, QColor color, QWidget* parent = nullptr);

    ////////////////////
    void set_digit(Digit digit);
    Digit digit() const noexcept { return _digit; }

    void set_color(QColor color);
    const QColor& color() const noexcept { return _color; }

    void reload();

signals:
    ////////////////////
    void digit_changed(Digit);
    void color_changed(const QColor&);

private:
    ////////////////////
    Digit _digit;
    QColor _color;
};

////////////////////////////////////////////////////////////////////////////////
#endif // DIGITWIDGET_HPP
