////////////////////////////////////////////////////////////////////////////////
#ifndef CLOCK_HPP
#define CLOCK_HPP

////////////////////////////////////////////////////////////////////////////////
#include <QDateTime>
#include <QObject>
#include <QTimer>

#include <utility>

////////////////////////////////////////////////////////////////////////////////
typedef int Seconds;

////////////////////////////////////////////////////////////////////////////////
class Clock : public QObject
{
    Q_OBJECT

public:
    ////////////////////
    Clock(QObject* parent = nullptr);

    Clock(Clock&& c) { swap(c); }
    Clock& operator=(Clock&& c) { swap(c); return *this; }

    void swap(Clock& c);

    ////////////////////
    const QDateTime& datetime() const noexcept { return _datetime; }
    QDate date() const { return datetime().date(); }
    QTime time() const { return datetime().time(); }

    ////////////////////
    void set_offset(Seconds seconds) { _offset = std::move(seconds); }
    const Seconds& offset() const noexcept { return _offset;}

    void add_offset(Seconds seconds) { set_offset(offset() + std::move(seconds)); }

    ////////////////////
    static Clock& instance();

signals:
    ////////////////////
    void datetime_changed(const QDateTime&);

private:
    ////////////////////
    Seconds _offset = 0;

    QTimer _update;
    void update();

    QDateTime _datetime;
};

////////////////////////////////////////////////////////////////////////////////
#endif // CLOCK_HPP
