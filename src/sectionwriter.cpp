////////////////////////////////////////////////////////////////////////////////
#include "sectionwriter.hpp"
#include <QXmlStreamReader>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

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

////////////////////////////////////////////////////////////////////////////////
QString SectionWriter::to_string(const Section::Duration& duration)
{
    std::time_t time = Section::Clock::to_time_t(Section::Timepoint(duration));

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%X");

    return ss.str().data();
}

////////////////////////////////////////////////////////////////////////////////
QString SectionWriter::to_string(const Section::Timepoint& timepoint)
{
    std::time_t time = Section::Clock::to_time_t(timepoint);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%c");

    return ss.str().data();
}
