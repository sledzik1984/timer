////////////////////////////////////////////////////////////////////////////////
#ifndef TIMEWIDGET_HPP
#define TIMEWIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include "digitwidget.hpp"
#include "freeze.hpp"
#include "numberwidget.hpp"

#include <QColor>
#include <QHBoxLayout>
#include <QTime>
#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
enum class Unit
{
    Hours, Minutes, Seconds
};

////////////////////////////////////////////////////////////////////////////////
class TimeWidget : public QWidget, public FreezingWidget
{
    Q_OBJECT

public:
    explicit TimeWidget(QTime time = QTime(0, 0), QColor color = Qt::black, QWidget* parent = nullptr);

    ////////////////////
    void set_time(QTime time);
    const QTime& time() const { return _time; }

    void set_color(QColor color);
    const QColor& color() const { return _color; }

    void reload();

signals:
    ////////////////////
    void hours_clicked();
    void hours_pressed();
    void hours_long_pressed();
    void hours_released();

    void minutes_clicked();
    void minutes_pressed();
    void minutes_long_pressed();
    void minutes_released();

    void seconds_clicked();
    void seconds_pressed();
    void seconds_long_pressed();
    void seconds_released();

    ////////////////////
    void clicked(Unit);
    void pressed(Unit);
    void long_pressed(Unit);
    void released(Unit);

    ////////////////////
    void time_changed(const QTime&);
    void color_changed(const QColor&);

protected:
    ////////////////////
    enum class Location { top, middle, bottom };
    Location location() const;

private:
    ////////////////////
    QTime _time;
    QColor _color;

    ////////////////////
    QHBoxLayout* _layout;

    NumberWidget* _hours;
     DigitWidget* _colon0;
    NumberWidget* _minutes;
     DigitWidget* _colon1;
    NumberWidget* _seconds;
};

////////////////////////////////////////////////////////////////////////////////
#endif // TIMEWIDGET_HPP
