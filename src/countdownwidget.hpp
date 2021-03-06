////////////////////////////////////////////////////////////////////////////////
#ifndef COUNTDOWNWIDGET_HPP
#define COUNTDOWNWIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include "timewidget.hpp"

#include <QTime>
#include <QTimer>
#include <QWidget>

#include <utility>

////////////////////////////////////////////////////////////////////////////////
class CountDownWidget : public TimeWidget
{
    Q_OBJECT

public:
    ////////////////////
    explicit CountDownWidget(QWidget* parent = nullptr);
    explicit CountDownWidget(QTime threshold, QWidget* parent = nullptr) : CountDownWidget(parent) { set_threshold(std::move(threshold)); }

    void reset();
    void set_threshold(QTime threshold);

signals:
    void time_reset();

private:
    ////////////////////
    void update(const QTime&);

    QTime _threshold;
    QTimer _blink, _stop;
};

////////////////////////////////////////////////////////////////////////////////
#endif // COUNTDOWNWIDGET_HPP
