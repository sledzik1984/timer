////////////////////////////////////////////////////////////////////////////////
#include "digitwidget.hpp"
#include "numberwidget.hpp"

#include <cmath>

////////////////////////////////////////////////////////////////////////////////
NumberWidget::NumberWidget(size_t number, const QColor& color, QWidget* parent) :
    QWidget(parent),
    _layout(new QHBoxLayout(this))
{
    _layout->setContentsMargins(0, 0, 0, 0);

    set_number(number);
    set_color(color);
    reload();

    connect(this, &NumberWidget::number_changed, this, &NumberWidget::reload);
    connect(this, &NumberWidget::color_changed, this, &NumberWidget::reload);

    connect(this, &NumberWidget::min_digits_changed, this, &NumberWidget::reload);
    connect(this, &NumberWidget::max_digits_changed, this, &NumberWidget::reload);
}

////////////////////////////////////////////////////////////////////////////////
void NumberWidget::set_number(size_t number)
{
    _number = number;
    emit number_changed(_number);
}

////////////////////////////////////////////////////////////////////////////////
void NumberWidget::set_color(const QColor& color)
{
    _color = color;
    emit color_changed(_color);
}

////////////////////////////////////////////////////////////////////////////////
void NumberWidget::set_min_digits(size_t n)
{
    _min_digits = n;
    emit min_digits_changed(n);
}

////////////////////////////////////////////////////////////////////////////////
void NumberWidget::set_max_digits(size_t n)
{
    _max_digits = n;
    emit max_digits_changed(n);
}

////////////////////////////////////////////////////////////////////////////////
void NumberWidget::reload()
{
    size_t digits = std::min(_max_digits, std::max(_min_digits, std::log10((double)_number) + 1));
    size_t number = _number;

    size_t count = _layout->count();
    size_t index = 1;

    while(index <= digits)
    {
        Digit digit = static_cast<Digit>(number % 10);
        number /= 10;

        if(index > count)
        {
            DigitWidget* widget = new DigitWidget(digit, _color);

            connect(widget, &DigitWidget::clicked     , this, &NumberWidget::clicked     );
            connect(widget, &DigitWidget::pressed     , this, &NumberWidget::pressed     );
            connect(widget, &DigitWidget::long_pressed, this, &NumberWidget::long_pressed);
            connect(widget, &DigitWidget::released    , this, &NumberWidget::released    );

            _layout->insertWidget(0, widget, widget->sizeHint().width());
            ++count;
        }
        else
        {
            auto widget = static_cast<DigitWidget*>(_layout->itemAt(count - index)->widget());

            widget->blockSignals(true);
            widget->set_digit(digit);
            widget->set_color(_color);
            widget->blockSignals(false);
        }

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
