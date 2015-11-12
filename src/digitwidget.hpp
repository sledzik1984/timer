////////////////////////////////////////////////////////////////////////////////
#ifndef DIGITWIDGET_HPP
#define DIGITWIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include "svgwidget.hpp"

#include <QColor>
#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
enum class Digit
{
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
    colon, period,
};

////////////////////////////////////////////////////////////////////////////////
class DigitWidget : public SvgWidget
{
    Q_OBJECT

public:
    explicit DigitWidget(Digit digit, const QColor& color = Qt::black, QWidget* parent = nullptr);

    ////////////////////
    void set_digit(Digit digit);
    Digit digit() const noexcept { return _digit; }

    void set_color(const QColor& color);
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
