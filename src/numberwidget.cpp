////////////////////////////////////////////////////////////////////////////////
#include "digitwidget.hpp"
#include "numberwidget.hpp"

#include <cmath>

////////////////////////////////////////////////////////////////////////////////
NumberWidget::NumberWidget(QWidget* parent) :
    NumberWidget(0, QColor(), parent)
{ }

////////////////////////////////////////////////////////////////////////////////
NumberWidget::NumberWidget(size_t number, QColor color, QWidget* parent) :
    QWidget(parent),
    _layout(new QHBoxLayout(this))
{
    _layout->setContentsMargins(0, 0, 0, 0);

    set_number(number);
    set_color(std::move(color));
    reload();

    connect(this, &NumberWidget::    number_changed, this, &NumberWidget::reload);
    connect(this, &NumberWidget::     color_changed, this, &NumberWidget::reload);
    connect(this, &NumberWidget::min_digits_changed, this, &NumberWidget::reload);
    connect(this, &NumberWidget::max_digits_changed, this, &NumberWidget::reload);
}

////////////////////////////////////////////////////////////////////////////////
void NumberWidget::set_number(size_t number)
{
    if(number != _number)
    {
        _number = number;
        emit number_changed(_number);
    }
}

////////////////////////////////////////////////////////////////////////////////
void NumberWidget::set_color(QColor color)
{
    if(color != _color)
    {
        _color = std::move(color);
        emit color_changed(_color);
    }
}

////////////////////////////////////////////////////////////////////////////////
void NumberWidget::set_min_digits(size_t n)
{
    if(n != _min_digits)
    {
        _min_digits = n;
        emit min_digits_changed(_min_digits);
    }
}

////////////////////////////////////////////////////////////////////////////////
void NumberWidget::set_max_digits(size_t n)
{
    if(n != _max_digits)
    {
        _max_digits = n;
        emit max_digits_changed(_max_digits);
    }
}

////////////////////////////////////////////////////////////////////////////////
void NumberWidget::set_min_max_digits(size_t min, size_t max)
{
    set_min_digits(min);
    set_max_digits(max);
}

////////////////////////////////////////////////////////////////////////////////
void NumberWidget::reload()
{
    size_t digits = std::max((double)_min_digits, 1 + (_number ? std::log10((double)_number) : 0));
    if(_max_digits) digits = std::min(_max_digits, digits);

    size_t number = _number;

    size_t count = _layout->count();
    size_t index = 1;

    while(index <= digits)
    {
        Digit digit = static_cast<Digit>(number % 10);
        number /= 10;

        DigitWidget* widget;
        if(index > count)
        {
            widget = new DigitWidget();

            connect(widget, &DigitWidget::clicked     , this, &NumberWidget::clicked     );
            connect(widget, &DigitWidget::pressed     , this, &NumberWidget::pressed     );
            connect(widget, &DigitWidget::long_pressed, this, &NumberWidget::long_pressed);
            connect(widget, &DigitWidget::released    , this, &NumberWidget::released    );

            _layout->insertWidget(0, widget, widget->sizeHint().width());
            ++count;
        }
        else widget = static_cast<DigitWidget*>(_layout->itemAt(count - index)->widget());

        widget->set_digit(digit);
        widget->set_color(_color);

        ++index;
    }

    while(index <= _max_digits)
    {
        DigitWidget* widget;
        if(index > count)
        {
            widget = new DigitWidget();

            connect(widget, &DigitWidget::clicked     , this, &NumberWidget::clicked     );
            connect(widget, &DigitWidget::pressed     , this, &NumberWidget::pressed     );
            connect(widget, &DigitWidget::long_pressed, this, &NumberWidget::long_pressed);
            connect(widget, &DigitWidget::released    , this, &NumberWidget::released    );

            _layout->insertWidget(0, widget, widget->sizeHint().width());
            ++count;
        }
        else widget = static_cast<DigitWidget*>(_layout->itemAt(count - index)->widget());

        widget->set_digit(Digit::none);
        widget->set_color(_color);

        ++index;
    }

    while(index <= count)
    {
        auto item = _layout->takeAt(0);

        delete item->widget();
        delete item;

        ++index;
    }
}
