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
    template<typename Rep, typename Period>
    inline Section(QString name, std::chrono::duration<Rep, Period> duration) :
        Section(std::move(name), std::chrono::duration_cast<std::chrono::seconds>(duration))
    { }

    Section(QString name, std::chrono::seconds duration) :
        _name(std::move(name)),
        _duration(duration)
    { }

    inline const QString& name() const noexcept { return _name; }
    inline const std::chrono::seconds duration() const noexcept { return _duration; }

private:
    QString _name;
    std::chrono::seconds _duration;
};

////////////////////////////////////////////////////////////////////////////////
#endif // SECTION_HPP
