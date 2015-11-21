////////////////////////////////////////////////////////////////////////////////
#ifndef CLOCK_HPP
#define CLOCK_HPP

////////////////////////////////////////////////////////////////////////////////
#include <QDateTime>
#include <QObject>
#include <QTimer>

////////////////////////////////////////////////////////////////////////////////
typedef int Seconds;

////////////////////////////////////////////////////////////////////////////////
class Clock : public QObject
{
    Q_OBJECT

public:
    Clock(QObject* parent = nullptr);

    ////////////////////
    const QDateTime& datetime() const noexcept { return _datetime; }
    QDate date() const { return datetime().date(); }
    QTime time() const { return datetime().time(); }

    ////////////////////
    void set_offset(Seconds);
    const Seconds& offset() const noexcept { return _offset;}

    void add_offset(Seconds);

    ////////////////////
    static Clock& instance();

signals:
    void offset_changed(const Seconds&);
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
