////////////////////////////////////////////////////////////////////////////////
#ifndef SECTION_HPP
#define SECTION_HPP

#include <QDateTime>
#include <QString>

#include <utility>

////////////////////////////////////////////////////////////////////////////////
typedef int Duration;

////////////////////////////////////////////////////////////////////////////////
class Section
{
public:
    ////////////////////
    Section() { reset(); }

    Section(QString name, Duration duration);

    ////////////////////
    Section(const Section&) = default;
    Section(Section&&) = default;

    Section& operator=(const Section&) = default;
    Section& operator=(Section&&) = default;

    ////////////////////
    void set_name(QString name) { _name = std::move(name); }
    const QString& name() const noexcept { return _name; }

    void set_duration(Duration duration) { _duration = std::move(duration); }
    const Duration& duration() const noexcept { return _duration; }

    ////////////////////
    void start();
    void end();
    void reset() { _started = _ended = QDateTime(); }

    const QDateTime& started() const noexcept { return _started; }
    const QDateTime& ended() const noexcept { return _ended; }

    bool is_started() const noexcept { return _started.isValid(); }
    bool is_ended() const noexcept { return _ended.isValid(); }

    Duration overage() const;

private:
    QString _name;
    Duration _duration { 0 };

    QDateTime _started;
    QDateTime _ended;

    ////////////////////
    void set_started(QDateTime datetime) { _started = std::move(datetime); }
    void set_ended(QDateTime datetime) { _ended = std::move(datetime); }

    friend class SectionReader;
};

////////////////////////////////////////////////////////////////////////////////
#endif // SECTION_HPP
