////////////////////////////////////////////////////////////////////////////////
#ifndef DIGITWIDGET_HPP
#define DIGITWIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include "presswidget.hpp"
#include "svgwidget.hpp"

#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
enum class Digit
{
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
    none,
};

////////////////////////////////////////////////////////////////////////////////
class DigitWidget : public SvgWidget, public PressWidget
{
    Q_OBJECT

public:
    ////////////////////
    explicit DigitWidget(QWidget* parent = nullptr) : DigitWidget(Digit::none, QColor(), parent) { }
    explicit DigitWidget(Digit digit, QColor color, QWidget* parent = nullptr);

    ////////////////////
    void set_digit(Digit digit);
    Digit digit() const noexcept { return _digit; }

    using SvgWidget::set_color; // make SvgWidget::set_color public

signals:
    ////////////////////
    void clicked() override;
    void pressed() override;
    void long_pressed() override;
    void released() override;

    void digit_changed(Digit);

private:
    ////////////////////
    Digit _digit;
};

////////////////////////////////////////////////////////////////////////////////
#endif // DIGITWIDGET_HPP
