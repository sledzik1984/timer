////////////////////////////////////////////////////////////////////////////////
#ifndef SECTION_HPP
#define SECTION_HPP

#include <QString>

#include <chrono>
#include <utility>

////////////////////////////////////////////////////////////////////////////////
using Duration = std::chrono::seconds;

using Clock = std::chrono::system_clock;
using Timepoint = std::chrono::time_point<Clock>;

////////////////////////////////////////////////////////////////////////////////
class Section
{
public:
    ////////////////////
    Section() { reset(); }

    template<typename Rep, typename Period>
    Section(QString name, const std::chrono::duration<Rep, Period>& duration) :
        Section(std::move(name), std::chrono::duration_cast<Duration>(duration))
    { }

    Section(QString name, Duration duration);

    ////////////////////
    Section(const Section&) = default;
    Section(Section&&) = default;

    Section& operator=(const Section&) = default;
    Section& operator=(Section&&) = default;

    ////////////////////
    void set_name(QString name) { _name = std::move(name); }
    const QString& name() const noexcept { return _name; }

    template<typename Rep, typename Period>
    void set_duration(const std::chrono::duration<Rep, Period>& duration)
    {
        set_duration(std::chrono::duration_cast<Duration>(duration));
    }

    void set_duration(Duration duration) { _duration = std::move(duration); }
    const Duration& duration() const noexcept { return _duration; }

    ////////////////////
    void start();
    void end();
    void reset() { _started = _ended = never; }

    const Timepoint& started() const noexcept { return _started; }
    const Timepoint& ended() const noexcept { return _ended; }

    bool is_started() const noexcept { return _started != never; }
    bool is_ended() const noexcept { return _ended != never; }

    Duration overage() const;

private:
    QString _name;
    Duration _duration { 0 };

    Timepoint _started;
    Timepoint _ended;

    static constexpr Timepoint never { };

    void set_started(Timepoint timepoint) { _started = std::move(timepoint); }
    void set_ended(Timepoint timepoint) { _ended = std::move(timepoint); }

    friend class SectionReader;
    friend class SectionWriter;
};

////////////////////////////////////////////////////////////////////////////////
QString to_string(const Duration&);
QString to_string(const Timepoint&);

Duration to_duration(const QString&);
Timepoint to_timepoint(const QString&);

////////////////////////////////////////////////////////////////////////////////
#endif // SECTION_HPP
