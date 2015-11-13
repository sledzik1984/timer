////////////////////////////////////////////////////////////////////////////////
#ifndef CLOCKWIDGET_HPP
#define CLOCKWIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include "timewidget.hpp"

#include <QColor>
#include <QTimer>
#include <QWidget>

////////////////////////////////////////////////////////////////////////////////
class ClockWidget : public TimeWidget
{
    Q_OBJECT

public:
    explicit ClockWidget(QColor color = Qt::red, QWidget* parent = nullptr);

    void set_offset(int offset) { _offset = offset; }
    int offset() const noexcept { return _offset;}

private:
    ////////////////////
    int _offset = 0;
    void add_offset(int amount);

    QTimer _update;
    void update();
};

////////////////////////////////////////////////////////////////////////////////
#endif // CLOCKWIDGET_HPP
