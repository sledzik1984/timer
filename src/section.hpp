////////////////////////////////////////////////////////////////////////////////
#ifndef SECTION_HPP
#define SECTION_HPP

#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include <chrono>
#include <utility>

////////////////////////////////////////////////////////////////////////////////
class Section
{
public:
    ////////////////////
    Section() = default;

    template<typename Rep, typename Period>
    Section(QString name, std::chrono::duration<Rep, Period> duration) :
        Section(std::move(name), std::chrono::duration_cast<std::chrono::seconds>(duration))
    { }

    Section(QString name, std::chrono::seconds duration)
    {
        set_name(std::move(name));
        set_duration(duration);
    }

    ////////////////////
    Section(const Section&) = default;
    Section(Section&&) = default;

    Section& operator=(const Section&) = default;
    Section& operator=(Section&&) = default;

    ////////////////////
    void set_name(QString name) { _name = std::move(name); }
    const QString& name() const noexcept { return _name; }

    ////////////////////
    template<typename Rep, typename Period>
    void set_duration(std::chrono::duration<Rep, Period> duration)
    {
        set_duration(std::chrono::duration_cast<std::chrono::seconds>(duration));
    }

    void set_duration(std::chrono::seconds duration) { _duration = duration; }
    const std::chrono::seconds duration() const noexcept { return _duration; }

protected:
    ////////////////////
    void read(QXmlStreamReader&);
    void write(QXmlStreamWriter&) const;
    friend class Event;

private:
    QString _name;
    std::chrono::seconds _duration;
};

////////////////////////////////////////////////////////////////////////////////
#endif // SECTION_HPP
