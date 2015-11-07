////////////////////////////////////////////////////////////////////////////////
#include "sectionwriter.hpp"
#include <QXmlStreamReader>

////////////////////////////////////////////////////////////////////////////////
void SectionWriter::write(QXmlStreamWriter& writer, const Section& section)
{
    ////////////////////
    // format: <section name="foo" duration="xx:xx:xx"/>

    writer.writeStartElement("section");
    writer.writeAttribute("name", section.name());
    writer.writeAttribute("time", section.time().toString("h:mm:ss"));
    writer.writeEndElement();
}
