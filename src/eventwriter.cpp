#include "eventwriter.hpp"
#include "sectionwriter.hpp"

#include <QXmlStreamWriter>

////////////////////////////////////////////////////////////////////////////////
void EventWriter::write(QXmlStreamWriter& writer, const Event& event)
{
    writer.writeStartElement("event");

    writer.writeAttribute("name", event.name());
    writer.writeAttribute("date", Event::to_string(event.date()));

    for(size_t n = 0; n < event.size(); ++n)
        SectionWriter::write(writer, event.section(n));

    writer.writeEndElement();
}
