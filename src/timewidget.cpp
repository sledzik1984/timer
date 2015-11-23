////////////////////////////////////////////////////////////////////////////////
#include "timewidget.hpp"

#include <QCursor>

////////////////////////////////////////////////////////////////////////////////
TimeWidget::TimeWidget(QColor color, Display format, QWidget* parent) :
    QWidget(parent),
    _layout (new QHBoxLayout(this))
{
    _layout->setContentsMargins(0, 0, 0, 0);

    ////////////////////
    if(static_cast<int>(format) & static_cast<int>(Display::Hrs))
    {
        _hours = new NumberWidget(0);
        _hours->set_min_max_digits(2, 2);
        _layout->addWidget(_hours , _hours ->sizeHint().width());

        connect(_hours, &NumberWidget::clicked     , this, &TimeWidget::hours_clicked     );
        connect(_hours, &NumberWidget::pressed     , this, &TimeWidget::hours_pressed     );
        connect(_hours, &NumberWidget::long_pressed, this, &TimeWidget::hours_long_pressed);
        connect(_hours, &NumberWidget::released    , this, &TimeWidget::hours_released    );

        connect(_hours, &NumberWidget::clicked     , [this](){ emit clicked     (Unit::Hours); });
        connect(_hours, &NumberWidget::pressed     , [this](){ emit pressed     (Unit::Hours); });
        connect(_hours, &NumberWidget::long_pressed, [this](){ emit long_pressed(Unit::Hours); });
        connect(_hours, &NumberWidget::released    , [this](){ emit released    (Unit::Hours); });

    }

    ////////////////////
    if(static_cast<int>(format) & static_cast<int>(Display::Min))
    {
        _minutes = new NumberWidget(0);
        if(_hours)
        {
            _colon0 = new DigitWidget(Digit::colon);
            _layout->addWidget(_colon0, _colon0->sizeHint().width());

            _minutes->set_min_max_digits(2, 2);
        }
        else _minutes->set_min_max_digits(1, 4);
        _layout->addWidget(_minutes, _minutes->sizeHint().width());

        connect(_minutes, &NumberWidget::clicked     , this, &TimeWidget::minutes_clicked     );
        connect(_minutes, &NumberWidget::pressed     , this, &TimeWidget::minutes_pressed     );
        connect(_minutes, &NumberWidget::long_pressed, this, &TimeWidget::minutes_long_pressed);
        connect(_minutes, &NumberWidget::released    , this, &TimeWidget::minutes_released    );

        connect(_minutes, &NumberWidget::clicked     , [this](){ emit clicked     (Unit::Minutes); });
        connect(_minutes, &NumberWidget::pressed     , [this](){ emit pressed     (Unit::Minutes); });
        connect(_minutes, &NumberWidget::long_pressed, [this](){ emit long_pressed(Unit::Minutes); });
        connect(_minutes, &NumberWidget::released    , [this](){ emit released    (Unit::Minutes); });
    }

    ////////////////////
    if(static_cast<int>(format) & static_cast<int>(Display::Sec))
    {
        _seconds = new NumberWidget(0);
        if(_minutes)
        {
            _colon1 = new DigitWidget(Digit::colon);
            _layout->addWidget(_colon1 , _colon1 ->sizeHint().width());

            _seconds->set_min_max_digits(2, 2);
        }
        else _seconds->set_min_max_digits(1, 5);
        _layout->addWidget(_seconds, _seconds->sizeHint().width());

        connect(_seconds, &NumberWidget::clicked     , this, &TimeWidget::seconds_clicked     );
        connect(_seconds, &NumberWidget::pressed     , this, &TimeWidget::seconds_pressed     );
        connect(_seconds, &NumberWidget::long_pressed, this, &TimeWidget::seconds_long_pressed);
        connect(_seconds, &NumberWidget::released    , this, &TimeWidget::seconds_released    );

        connect(_seconds, &NumberWidget::clicked     , [this](){ emit clicked     (Unit::Seconds); });
        connect(_seconds, &NumberWidget::pressed     , [this](){ emit pressed     (Unit::Seconds); });
        connect(_seconds, &NumberWidget::long_pressed, [this](){ emit long_pressed(Unit::Seconds); });
        connect(_seconds, &NumberWidget::released    , [this](){ emit released    (Unit::Seconds); });
    }

    ////////////////////
    set_time(QTime(0, 0));
    set_color(std::move(color));
    reload();

    connect(this, &TimeWidget:: time_changed, this, &TimeWidget::reload);
    connect(this, &TimeWidget::color_changed, this, &TimeWidget::reload);
}

////////////////////////////////////////////////////////////////////////////////
void TimeWidget::set_time(QTime time)
{
    if(time != _time)
    {
        _time = std::move(time);
        emit time_changed(_time);
    }
}

////////////////////////////////////////////////////////////////////////////////
void TimeWidget::set_color(QColor color)
{
    if(color != _color)
    {
        _color = std::move(color);
        emit color_changed(_color);
    }
}

////////////////////////////////////////////////////////////////////////////////
void TimeWidget::reload()
{
    int value = _time.hour();
    if(_hours)
    {
        {
            NumberWidget::Freeze _(_hours);
            _hours->set_number(value);
            value = 0;
            _hours->set_color(_color);
        }
        _hours->reload();
    }
    else value *= 60;

    if(_colon0) _colon0->set_color(_color);

    value += _time.minute();
    if(_minutes)
    {
        {
            NumberWidget::Freeze _(_minutes);
            _minutes->set_number(value);
            value = 0;
            _minutes->set_color(_color);
        }
        _minutes->reload();
    }
    else value *= 60;

    if(_colon1) _colon1->set_color(_color);

    value += _time.second();
    if(_seconds)
    {
        {
            NumberWidget::Freeze _(_seconds);
            _seconds->set_number(value);
            value = 0;
            _seconds->set_color(_color);
        }
        _seconds->reload();
    }
}

////////////////////////////////////////////////////////////////////////////////
TimeWidget::Location TimeWidget::location() const
{
    QPoint cursor = mapFromGlobal(QCursor::pos());

    if(cursor.y() <= height() / 4)
        return Location::top;

    else if(cursor.y() >= height() * 3 / 4)
        return Location::bottom;

    else return Location::middle;
}
