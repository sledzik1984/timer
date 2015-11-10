////////////////////////////////////////////////////////////////////////////////
#include "sectionwriter.hpp"

#include <QDateTime>
#include <QString>
#include <QTime>

////////////////////////////////////////////////////////////////////////////////
static inline QString to_string(const Duration& duration)
{
    return QTime(0, 0).addSecs(duration).toString("H:mm:ss");
}

////////////////////////////////////////////////////////////////////////////////
static inline QString to_string(const QDateTime& datetime)
{
    return datetime.toString("MMM d h:mm:ss yyyy");
}

////////////////////////////////////////////////////////////////////////////////
void SectionWriter::write(QXmlStreamWriter& writer, const Section& section)
{
    ////////////////////
    // format: <section name="foo" duration="<time>" [started="<date/time>"] [ended="date/time"]/>

    writer.writeStartElement("section");

    writer.writeAttribute("name", section.name());
    writer.writeAttribute("duration", to_string(section.duration()));

    if(section.is_started()) writer.writeAttribute("started", to_string(section.started()));
    if(section.is_ended()) writer.writeAttribute("ended", to_string(section.ended()));

    writer.writeEndElement();
}
