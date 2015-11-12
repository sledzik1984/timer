////////////////////////////////////////////////////////////////////////////////
#include "digitwidget.hpp"

#include <QByteArray>

////////////////////////////////////////////////////////////////////////////////
static const QByteArray head = "<svg viewBox=\"0 0 500 790\" fill=\"%color%\">";
static const QByteArray foot = "</svg>";

////////////////////////////////////////////////////////////////////////////////
static const QByteArray segment[]
{
    "<path id=\"0\" d=\"m70,60 360,0 -70,70 -220,0 -70,-70 z\"/>",
    "<path id=\"1\" d=\"m440,70 0,290 -30,30 -40,-40 0,-210 70,-70 z\"/>",
    "<path id=\"2\" d=\"m440,430 0,290 -70,-70 0,-210 40,-40 30,30 z\"/>",
    "<path id=\"3\" d=\"m430,730 -360,0 70,-70 220,0 70,70 z\"/>",
    "<path id=\"4\" d=\"m130,440 0,210 -70,70 0,-290 30,-30 40,40 z\"/>",
    "<path id=\"5\" d=\"m130,140 0,210 -40,40 -30,-30 0,-290 70,70 z\"/>",
    "<path id=\"6\" d=\"m140,360 220,0 35,35 -35,35 -220,0 -35,-35 35,-35 z\"/>",
};

////////////////////////////////////////////////////////////////////////////////
static const QByteArray digit[]
{
    head + segment[0] + segment[1] + segment[2] + segment[3] + segment[4] + segment[5] +              foot, // 0
    head +              segment[1] + segment[2] +                                                     foot, // 1
    head + segment[0] + segment[1] +              segment[3] + segment[4] +              segment[6] + foot, // 2
    head + segment[0] + segment[1] + segment[2] + segment[3] +                           segment[6] + foot, // 3
    head +              segment[1] + segment[2] +                           segment[5] + segment[6] + foot, // 4
    head + segment[0] +              segment[2] + segment[3] +              segment[5] + segment[6] + foot, // 5
    head + segment[0] +              segment[2] + segment[3] + segment[4] + segment[5] + segment[6] + foot, // 6
    head + segment[0] + segment[1] + segment[2] +                                                     foot, // 7
    head + segment[0] + segment[1] + segment[2] + segment[3] + segment[4] + segment[5] + segment[6] + foot, // 8
    head + segment[0] + segment[1] + segment[2] + segment[3] +              segment[5] + segment[6] + foot, // 9

    "<svg viewBox=\"0 0 190 790\" fill=\"%color%\"><circle cx=\"95\" cy=\"240\" r=\"35\"/><circle cx=\"95\" cy=\"550\" r=\"35\"/></svg>", // colon
    "<svg viewBox=\"0 0 190 790\" fill=\"%color%\"><circle cx=\"95\" cy=\"695\" r=\"35\"/></svg>", // period
};

////////////////////////////////////////////////////////////////////////////////
DigitWidget::DigitWidget(Digit digit, QColor color, QWidget* parent) :
    SvgWidget(parent)
{
    set_digit(digit);
    set_color(std::move(color));
    reload();

    connect(this, &DigitWidget::digit_changed, this, &DigitWidget::reload);
    connect(this, &DigitWidget::color_changed, this, &DigitWidget::reload);
}

////////////////////////////////////////////////////////////////////////////////
void DigitWidget::set_digit(Digit digit)
{
    _digit = digit;
    emit digit_changed(_digit);
}

////////////////////////////////////////////////////////////////////////////////
void DigitWidget::set_color(QColor color)
{
    _color = std::move(color);
    emit color_changed(_color);
}

////////////////////////////////////////////////////////////////////////////////
void DigitWidget::reload()
{
    QByteArray contents = ::digit[static_cast<size_t>(_digit)];
    contents.replace("%color%", _color.name().toLatin1());
    load(contents);
}
