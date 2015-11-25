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

    Seconds period() const;
    Seconds real_period() const;

    ////////////////////
    size_t size() const noexcept { return _sections.size(); }

    const Section::Pointer& section(size_t n) const;
    Section::Pointer& section(size_t n);

    void clear();

    void insert(size_t n, Section::Pointer section);
    void append(Section::Pointer section) { insert(size(), std::move(section)); }

    void erase(size_t n);

    ////////////////////
    QDateTime started() const;
    QDateTime ended() const;

    Seconds overage() const;

    bool start();
    bool next();
    void reset();

    int current() const noexcept { return _current; }

    ////////////////////
    static Event::Pointer instance();

signals:
    ////////////////////
    void name_changed(const QString&);
    void date_changed(const QDate&);

    void section_inserted(size_t n);
    void section_erased(size_t n);

    void started_changed(const QDateTime&);
    void ended_changed(const QDateTime&);

    void current_changed(int);

private:
    ////////////////////
    QString _name;
    QDate _date;
    Sections _sections;

    static constexpr int none = -1;
    int _current = none;

    ////////////////////
    void set_current(int);

    void insert(Sections::const_iterator, Section::Pointer section);
    void erase(Sections::const_iterator);

    Sections::const_iterator begin() const { return _sections.begin(); }
    Sections::const_iterator end() const { return _sections.end(); }

    Sections::const_reverse_iterator rbegin() const { return _sections.rbegin(); }
    Sections::const_reverse_iterator rend() const { return _sections.rend(); }
};

////////////////////////////////////////////////////////////////////////////////
#endif // EVENT_HPP
