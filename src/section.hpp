////////////////////////////////////////////////////////////////////////////////
#ifndef SECTION_HPP
#define SECTION_HPP

////////////////////////////////////////////////////////////////////////////////
#include "clock.hpp"

#include <QDateTime>
#include <QString>

#include <utility>

////////////////////////////////////////////////////////////////////////////////
class Section
{
public:
    Section() { reset(); }
    Section(QString name, Seconds duration);

    ////////////////////
    Section(const Section&) = default;
    Section(Section&&) = default;

    Section& operator=(const Section&) = default;
    Section& operator=(Section&&) = default;

    ////////////////////
    void set_name(QString name) { _name = std::move(name); }
    const QString& name() const noexcept { return _name; }

    void set_duration(Seconds seconds) { _duration = std::move(seconds); }
    const Seconds& duration() const noexcept { return _duration; }

    ////////////////////
    void start();
    void end();
    void reset() { _started = _ended = QDateTime(); }

    const QDateTime& started() const noexcept { return _started; }
    const QDateTime& ended() const noexcept { return _ended; }

    bool is_started() const noexcept { return _started.isValid(); }
    bool is_ended() const noexcept { return _ended.isValid(); }

    Seconds overage() const;

private:
    QString _name;
    Seconds _duration { 0 };

    QDateTime _started;
    QDateTime _ended;

    ////////////////////
    void set_started(QDateTime datetime) { _started = std::move(datetime); }
    void set_ended(QDateTime datetime) { _ended = std::move(datetime); }

    friend class SectionReader;
};

////////////////////////////////////////////////////////////////////////////////
#endif // SECTION_HPP
