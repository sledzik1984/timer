////////////////////////////////////////////////////////////////////////////////
#ifndef SECTION_HPP
#define SECTION_HPP

#include <QString>
#include <QTime>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include <utility>

////////////////////////////////////////////////////////////////////////////////
class Section
{
public:
    ////////////////////
    Section() = default;

    Section(QString name, QTime time)
    {
        set_name(std::move(name));
        set_time(std::move(time));
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
    void set_time(QTime time) { _time = std::move(time); }
    const QTime& time() const noexcept { return _time; }

protected:
    ////////////////////
    void read(QXmlStreamReader&);
    void write(QXmlStreamWriter&) const;
    friend class Event;

private:
    QString _name;
    QTime _time { 0, 0, 0 };
};

////////////////////////////////////////////////////////////////////////////////
#endif // SECTION_HPP
