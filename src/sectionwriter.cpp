////////////////////////////////////////////////////////////////////////////////
#include "sectionwriter.hpp"
#include <QXmlStreamReader>

////////////////////////////////////////////////////////////////////////////////
void SectionWriter::write(QXmlStreamWriter& writer, const Section& section)
{
    ////////////////////
    // format: <section name="foo" duration="<time>" [started="<date/time>"] [ended="date/time"]/>

    writer.writeStartElement("section");

    writer.writeAttribute("name", section.name());
    writer.writeAttribute("duration", Section::to_string(section.duration()));

    if(section.is_started()) writer.writeAttribute("started", Section::to_string(section.started()));
    if(section.is_ended()) writer.writeAttribute("ended", Section::to_string(section.ended()));

    writer.writeEndElement();
}
