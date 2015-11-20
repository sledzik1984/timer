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

    void set_offset(int);
    int offset() const noexcept { return _offset;}

signals:
    void offset_changed(int);

private:
    ////////////////////
    int _offset = 0;

    void proc_clicked(Unit unit);

    QTimer _update;
    void update();
};

////////////////////////////////////////////////////////////////////////////////
#endif // CLOCKWIDGET_HPP
