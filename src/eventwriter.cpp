////////////////////////////////////////////////////////////////////////////////
#include "eventwriter.hpp"
#include "sectionwriter.hpp"
#include "error.hpp"

#include <QDate>
#include <QFile>

////////////////////////////////////////////////////////////////////////////////
static inline QString to_string(const QDate& date)
{
    return date.toString("MMM d yyyy");
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void EventWriter::write(const QString& filename, const Event::Pointer& event)
{
    QFile file(filename);
    if(!file.open(QFile::WriteOnly)) throw XmlError(file.errorString());

    EventWriter::write(&file, event);
    if(file.error()) throw XmlError(file.errorString());
}

////////////////////////////////////////////////////////////////////////////////
void EventWriter::write(QIODevice* device, const Event::Pointer& event)
{
    QXmlStreamWriter writer(device);
    writer.setAutoFormatting(true);

    EventWriter::write(writer, event);
    if(writer.hasError()) throw XmlError(device->errorString());
}

////////////////////////////////////////////////////////////////////////////////
void EventWriter::write(QXmlStreamWriter& writer, const Event::Pointer& event)
{
    writer.writeStartElement("event");

    writer.writeAttribute("name", event->name());
    writer.writeAttribute("date", to_string(event->date()));

    for(size_t n = 0; n < event->size(); ++n) SectionWriter::write(writer, event->section(n));

    writer.writeEndElement();
}
