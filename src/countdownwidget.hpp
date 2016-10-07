////////////////////////////////////////////////////////////////////////////////
#ifndef COUNTDOWNWIDGET_HPP
#define COUNTDOWNWIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include "timewidget.hpp"

#include <QColor>
#include <QTime>

#include <utility>

////////////////////////////////////////////////////////////////////////////////
class CountDownWidget : public TimeWidget
{
    Q_OBJECT

public:
    ////////////////////
    CountDownWidget(QColor color, QColor color_lo, QTime time_lo, QWidget* parent = nullptr);
    explicit CountDownWidget(QColor color, QWidget* parent = nullptr) : CountDownWidget(color, color, QTime(0, 0, 0), parent) { }

    void reset();

private:
    void update(const QTime&);

    QColor _color, _color_lo;
    QTime _time_lo;
};

////////////////////////////////////////////////////////////////////////////////
#endif // COUNTDOWNWIDGET_HPP
