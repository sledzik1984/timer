#include "eventwriter.hpp"
#include "sectionwriter.hpp"

#include <QString>
#include <QDate>

////////////////////////////////////////////////////////////////////////////////
static inline QString to_string(const QDate& date)
{
    return date.toString("MMM d yyyy");
}

////////////////////////////////////////////////////////////////////////////////
void EventWriter::write(QXmlStreamWriter& writer, const Event& event)
{
    writer.writeStartElement("event");

    writer.writeAttribute("name", event.name());
    writer.writeAttribute("date", to_string(event.date()));

    for(size_t n = 0; n < event.size(); ++n) SectionWriter::write(writer, event.section(n));

    writer.writeEndElement();
}
