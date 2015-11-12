////////////////////////////////////////////////////////////////////////////////
#ifndef EVENTWRITER_HPP
#define EVENTWRITER_HPP

#include "event.hpp"

#include <QIODevice>
#include <QString>
#include <QXmlStreamWriter>

////////////////////////////////////////////////////////////////////////////////
class EventWriter
{
public:
    static void write(const QString& filename, const Event&);
    static void write(QIODevice*, const Event&);
    static void write(QXmlStreamWriter&, const Event&);
};

////////////////////////////////////////////////////////////////////////////////
#endif // EVENTWRITER_HPP
