////////////////////////////////////////////////////////////////////////////////
#ifndef NUMBERWIDGET_HPP
#define NUMBERWIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include <QColor>
#include <QHBoxLayout>
#include <QWidget>

#include <climits>

////////////////////////////////////////////////////////////////////////////////
class NumberWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NumberWidget(QWidget* parent = nullptr);
    NumberWidget(size_t number, QColor color, QWidget* parent = nullptr);

    ////////////////////
    void set_number(size_t number);
    size_t number() const noexcept { return _number; }

    void set_color(QColor color);
    const QColor& color() const noexcept{ return _color; }

    void set_min_digits(size_t n);
    size_t min_digits() const noexcept { return _min_digits; }

    void set_max_digits(size_t n);
    size_t max_digits() const noexcept { return _max_digits; }

    void set_min_max_digits(size_t min, size_t max);

    void reload();

signals:
    ////////////////////
    void clicked();
    void pressed();
    void long_pressed();
    void released();

    void number_changed(size_t);
    void color_changed(const QColor&);

    void min_digits_changed(size_t);
    void max_digits_changed(size_t);

private:
    ////////////////////
    size_t _number;
    QColor _color;

    size_t _min_digits = 0;
    size_t _max_digits = 0;

    QHBoxLayout* _layout;
};

////////////////////////////////////////////////////////////////////////////////
#endif // NUMBERWIDGET_HPP
