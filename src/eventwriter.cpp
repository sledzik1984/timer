#include "eventwriter.hpp"
#include "sectionwriter.hpp"

////////////////////////////////////////////////////////////////////////////////
void EventWriter::write(QXmlStreamWriter& writer, const Event& event)
{
    writer.writeStartElement("event");
    writer.writeAttribute("name", event.name());
    for(const Section& section: event.sections()) SectionWriter::write(writer, section);
    writer.writeEndElement();
}
