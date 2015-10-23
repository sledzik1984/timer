////////////////////////////////////////////////////////////////////////////////
#ifndef SECTION_HPP
#define SECTION_HPP

#include <QObject>
#include <QString>

#include <chrono>
#include <utility>

////////////////////////////////////////////////////////////////////////////////
class Section : public QObject
{
    Q_OBJECT

public:
    ////////////////////
    template<typename Rep, typename Period>
    Section(QString name, std::chrono::duration<Rep, Period> duration) :
        Section(std::move(name), std::chrono::duration_cast<std::chrono::seconds>(duration))
    { }

    Section(QString name, std::chrono::seconds duration) :
        _name(std::move(name)),
        _duration(duration)
    { }

    ////////////////////
    void set_name(QString name)
    {
        _name = std::move(name);
        emit name_changed(_name);
    }

    const QString& name() const noexcept { return _name; }

    ////////////////////
    template<typename Rep, typename Period>
    void set_duration(std::chrono::duration<Rep, Period> duration)
    {
        set_duration(std::chrono::duration_cast<std::chrono::seconds>(duration));
    }

    void set_duration(std::chrono::seconds duration)
    {
        _duration = duration;
        emit duration_changed(_duration);
    }

    const std::chrono::seconds duration() const noexcept { return _duration; }

signals:
    void name_changed(const QString&);
    void duration_changed(std::chrono::seconds);

private:
    QString _name;
    std::chrono::seconds _duration;
};

////////////////////////////////////////////////////////////////////////////////
#endif // SECTION_HPP
