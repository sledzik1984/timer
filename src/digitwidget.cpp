////////////////////////////////////////////////////////////////////////////////
#include "digitwidget.hpp"

#include <QByteArray>
#include <QRect>

////////////////////////////////////////////////////////////////////////////////
static const QRect viewbox = { 0, 0, 500, 790 };

////////////////////////////////////////////////////////////////////////////////
static const QByteArray segment[] =
{
    R"(<path id="0" d="m70,60 360,0 -70,70 -220,0 -70,-70 z"/>)",
    R"(<path id="1" d="m440,70 0,290 -30,30 -40,-40 0,-210 70,-70 z"/>)",
    R"(<path id="2" d="m440,430 0,290 -70,-70 0,-210 40,-40 30,30 z"/>)",
    R"(<path id="3" d="m430,730 -360,0 70,-70 220,0 70,70 z"/>)",
    R"(<path id="4" d="m130,440 0,210 -70,70 0,-290 30,-30 40,40 z"/>)",
    R"(<path id="5" d="m130,140 0,210 -40,40 -30,-30 0,-290 70,70 z"/>)",
    R"(<path id="6" d="m140,360 220,0 35,35 -35,35 -220,0 -35,-35 35,-35 z"/>)",
};

////////////////////////////////////////////////////////////////////////////////
static const QByteArray digit[] =
{
    segment[0] + segment[1] + segment[2] + segment[3] + segment[4] + segment[5]             , // 0
                 segment[1] + segment[2]                                                    , // 1
    segment[0] + segment[1] +              segment[3] + segment[4] +              segment[6], // 2
    segment[0] + segment[1] + segment[2] + segment[3] +                           segment[6], // 3
                 segment[1] + segment[2] +                           segment[5] + segment[6], // 4
    segment[0] +              segment[2] + segment[3] +              segment[5] + segment[6], // 5
    segment[0] +              segment[2] + segment[3] + segment[4] + segment[5] + segment[6], // 6
    segment[0] + segment[1] + segment[2]                                                    , // 7
    segment[0] + segment[1] + segment[2] + segment[3] + segment[4] + segment[5] + segment[6], // 8
    segment[0] + segment[1] + segment[2] + segment[3] +              segment[5] + segment[6], // 9
    ""                                                                                      , // none
};

////////////////////////////////////////////////////////////////////////////////
DigitWidget::DigitWidget(Digit digit, QColor color, QWidget* parent) :
    SvgWidget(::viewbox, color, QByteArray(), parent),
    PressWidget(this)
{
    set_digit(digit);
    reload();
}

////////////////////////////////////////////////////////////////////////////////
void DigitWidget::set_digit(Digit digit)
{
    if(digit != _digit)
    {
        _digit = digit;
        emit digit_changed(_digit);

        set_contents(::digit[static_cast<size_t>(_digit)]);
    }
}
