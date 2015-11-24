////////////////////////////////////////////////////////////////////////////////
#ifndef SECTION_HPP
#define SECTION_HPP

////////////////////////////////////////////////////////////////////////////////
#include "clock.hpp"

#include <QDateTime>
#include <QObject>
#include <QString>

#include <utility>

////////////////////////////////////////////////////////////////////////////////
class Section : public QObject
{
    Q_OBJECT

public:
    ////////////////////
    Section() = default;
    Section(QString name, Seconds duration);

    Section(Section&& s) { swap(s); }
    Section& operator=(Section&& s) { swap(s); return *this; }

    void swap(Section& s);

    ////////////////////
    void set_name(QString name);
    const QString& name() const noexcept { return _name; }

    void set_duration(Seconds duration);
    const Seconds& duration() const noexcept { return _duration; }

    ////////////////////
    const QDateTime& started() const noexcept { return _started; }
    const QDateTime& ended() const noexcept { return _ended; }

    bool is_started() const noexcept { return started().isValid(); }
    bool is_ended() const noexcept { return ended().isValid(); }

    Seconds overage() const;

protected:
    ////////////////////
    void start();
    void end();
    void reset();

    friend class Event;

signals:
    ////////////////////
    void name_changed(const QString&);
    void duration_changed(const Seconds&);

    void started_changed(const QDateTime&);
    void ended_changed(const QDateTime&);

private:
    ////////////////////
    QString _name;
    Seconds _duration = 0;

    QDateTime _started;
    QDateTime _ended;

    ////////////////////
    void set_started(QDateTime started);
    void set_ended(QDateTime ended);

    friend class SectionReader;
};

////////////////////////////////////////////////////////////////////////////////
#endif // SECTION_HPP
