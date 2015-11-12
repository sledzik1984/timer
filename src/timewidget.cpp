////////////////////////////////////////////////////////////////////////////////
#include "block.hpp"
#include "timewidget.hpp"

////////////////////////////////////////////////////////////////////////////////
TimeWidget::TimeWidget(QTime time, QColor color, QWidget* parent) :
    QWidget(parent),
    _layout (new QHBoxLayout(this)),
    _hours  (new NumberWidget(0)),
    _colon0 (new DigitWidget(Digit::colon)),
    _minutes(new NumberWidget(0)),
    _colon1 (new DigitWidget(Digit::colon)),
    _seconds(new NumberWidget(0))
{
    ////////////////////
    _layout->setContentsMargins(0, 0, 0, 0);

    _hours  ->set_min_max_digits(2, 2);
    _minutes->set_min_max_digits(2, 2);
    _seconds->set_min_max_digits(2, 2);

    _layout->addWidget(_hours  , _hours  ->sizeHint().width());
    _layout->addWidget(_colon0 , _colon0 ->sizeHint().width());
    _layout->addWidget(_minutes, _minutes->sizeHint().width());
    _layout->addWidget(_colon1 , _colon1 ->sizeHint().width());
    _layout->addWidget(_seconds, _seconds->sizeHint().width());

    ////////////////////
    connect(_hours  , &NumberWidget::clicked     , this, &TimeWidget::hours_clicked       );
    connect(_hours  , &NumberWidget::pressed     , this, &TimeWidget::hours_long_pressed  );
    connect(_hours  , &NumberWidget::long_pressed, this, &TimeWidget::hours_long_pressed  );
    connect(_hours  , &NumberWidget::released    , this, &TimeWidget::hours_released      );

    connect(_minutes, &NumberWidget::clicked     , this, &TimeWidget::minutes_clicked     );
    connect(_minutes, &NumberWidget::pressed     , this, &TimeWidget::minutes_long_pressed);
    connect(_minutes, &NumberWidget::long_pressed, this, &TimeWidget::minutes_long_pressed);
    connect(_minutes, &NumberWidget::released    , this, &TimeWidget::minutes_released    );

    connect(_seconds, &NumberWidget::clicked     , this, &TimeWidget::seconds_clicked     );
    connect(_seconds, &NumberWidget::pressed     , this, &TimeWidget::seconds_long_pressed);
    connect(_seconds, &NumberWidget::long_pressed, this, &TimeWidget::seconds_long_pressed);
    connect(_seconds, &NumberWidget::released    , this, &TimeWidget::seconds_released    );

    ////////////////////
    set_time(std::move(time));
    set_color(std::move(color));
    reload();

    connect(this, &TimeWidget:: time_changed, this, &TimeWidget::reload);
    connect(this, &TimeWidget::color_changed, this, &TimeWidget::reload);
}

////////////////////////////////////////////////////////////////////////////////
void TimeWidget::set_time(QTime time)
{
    _time = std::move(time);
    emit time_changed(_time);
}

////////////////////////////////////////////////////////////////////////////////
void TimeWidget::set_color(QColor color)
{
    _color = std::move(color);
    emit color_changed(_color);
}

////////////////////////////////////////////////////////////////////////////////
void TimeWidget::reload()
{
    {
        Block _(_hours);
        _hours->set_number(_time.hour());
        _hours->set_color(_color);
    }
    _hours->reload();

    _colon0->set_color(_color);
    {
        Block _(_minutes);
        _minutes->set_number(_time.minute());
        _minutes->set_color(_color);
    }
    _minutes->reload();

    _colon1->set_color(_color);
    {
        Block _(_seconds);
        _seconds->set_number(_time.second());
        _seconds->set_color(_color);
    }
    _seconds->reload();
}
