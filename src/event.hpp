////////////////////////////////////////////////////////////////////////////////
#ifndef EVENT_HPP
#define EVENT_HPP

////////////////////////////////////////////////////////////////////////////////
#include "section.hpp"

#include <QDate>
#include <QDateTime>
#include <QObject>
#include <QString>

#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
using Sections = std::vector<Section>;

////////////////////////////////////////////////////////////////////////////////
class Event : public QObject
{
    Q_OBJECT

public:
    ////////////////////
    Event() = default;
    Event(QString name, QDate date);

    Event(const Event&) = delete;
    Event(Event&& e) { swap(e); }

    Event& operator=(const Event&) = delete;
    Event& operator=(Event&& e) { swap(e); return *this; }

    void swap(Event&);

    ////////////////////
    void set_name(QString name);
    const QString& name() const noexcept { return _name; }

    void set_date(QDate date);
    const QDate& date() const noexcept { return _date; }

    Seconds duration() const;

    ////////////////////
    size_t size() const noexcept { return _sections.size(); }

    const Section& section(size_t n) const;
    Section& section(size_t n);

    void clear();

    void insert(size_t n, Section section);
    void insert(Section section) { insert(size(), std::move(section)); }

    void erase(size_t n);

    ////////////////////
    void reset();
    void next();

    size_t current() const noexcept { return _current; }
    static constexpr size_t none = -1;

    const QDateTime& started() const { return section(0).started(); }
    const QDateTime& ended() const { return section(size() - 1).ended(); }

    bool is_started() const { return size() && section(0).is_started(); }
    bool is_ended() const { return size() && section(size() - 1).is_ended(); }

    Seconds overage() const;

    ////////////////////
    static Event& instance();

signals:
    ////////////////////
    void name_changed(const QString&);
    void date_changed(const QDate&);

private:
    ////////////////////
    QString _name;
    QDate _date;
    Sections _sections;

    size_t _current = none;
};

////////////////////////////////////////////////////////////////////////////////
#endif // EVENT_HPP
