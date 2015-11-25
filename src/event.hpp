////////////////////////////////////////////////////////////////////////////////
#ifndef EVENT_HPP
#define EVENT_HPP

////////////////////////////////////////////////////////////////////////////////
#include "section.hpp"

#include <QDate>
#include <QDateTime>
#include <QObject>
#include <QString>

#include <memory>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
using Sections = std::vector<Section::Pointer>;

////////////////////////////////////////////////////////////////////////////////
class Event : public QObject
{
    Q_OBJECT

public:
    ////////////////////
    using Pointer = std::shared_ptr<Event>;

    ////////////////////
    Event() = default;
    Event(QString name, QDate date);

    void replace(Event::Pointer&&);

    ////////////////////
    void set_name(QString name);
    const QString& name() const noexcept { return _name; }

    void set_date(QDate date);
    const QDate& date() const noexcept { return _date; }

    Seconds duration() const;

    ////////////////////
    size_t size() const noexcept { return _sections.size(); }

    const Section::Pointer& section(size_t n) const;
    Section::Pointer& section(size_t n);

    void clear();

    void insert(size_t n, Section::Pointer section);
    void insert(Section::Pointer section) { insert(size(), std::move(section)); }

    void erase(size_t n);

    ////////////////////
    QDateTime started() const;
    QDateTime ended() const;

    bool is_started() const { return started().isValid(); }
    bool is_ended() const { return ended().isValid(); }

    Seconds overage() const;

    void start();
    void next();
    void reset();

    ////////////////////
    static Event::Pointer instance();

signals:
    ////////////////////
    void name_changed(const QString&);
    void date_changed(const QDate&);

    void duration_changed(const Seconds&);

private:
    ////////////////////
    QString _name;
    QDate _date;
    Sections _sections;

    void update_duration();
};

////////////////////////////////////////////////////////////////////////////////
#endif // EVENT_HPP
