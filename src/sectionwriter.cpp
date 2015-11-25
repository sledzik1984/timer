////////////////////////////////////////////////////////////////////////////////
#include "sectionwriter.hpp"

#include <QDateTime>
#include <QString>
#include <QTime>

////////////////////////////////////////////////////////////////////////////////
static inline QString to_string(const Seconds& period)
{
    return QTime(0, 0).addSecs(period).toString("H:mm:ss");
}

////////////////////////////////////////////////////////////////////////////////
static inline QString to_string(const QDateTime& datetime)
{
    return datetime.toString("MMM d h:mm:ss yyyy");
}

////////////////////////////////////////////////////////////////////////////////
void SectionWriter::write(QXmlStreamWriter& writer, const Section::Pointer& section)
{
    ////////////////////
    // format: <section name="foo" period="<time>" [started="<date/time>"] [ended="date/time"]/>

    writer.writeStartElement("section");

    writer.writeAttribute("name", section->name());
    writer.writeAttribute("period", to_string(section->period()));

    if(section->is_started()) writer.writeAttribute("started", to_string(section->started()));
    if(section->is_ended()) writer.writeAttribute("ended", to_string(section->ended()));

    writer.writeEndElement();
}
