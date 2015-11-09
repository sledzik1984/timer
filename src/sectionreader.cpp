////////////////////////////////////////////////////////////////////////////////
#include "sectionreader.hpp"
#include "xmlerror.hpp"

#include <QXmlStreamReader>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
Section SectionReader::read(QXmlStreamReader& reader)
{
    ////////////////////
    // format: <section name="foo" duration="<time>" [started="<date/time>"] [ended="date/time"]/>

    ////////////////////
    // check opening tag
    if(reader.tokenType() != QXmlStreamReader::StartElement
    || reader.name() != "section")
    throw XmlError("Expecting section start element");

    ////////////////////
    // get section attributes
    Section section;
    auto attrs = reader.attributes();

    if(!attrs.hasAttribute("name"))
        throw XmlError("Missing name attribute");
    section.set_name(attrs.value("name").toString());

    if(!attrs.hasAttribute("duration"))
        throw XmlError("Missing duration attribute");
    section.set_duration(to_duration(attrs.value("duration").toString()));

    if(attrs.hasAttribute("started"))
        section.set_started(to_timepoint(attrs.value("started").toString()));

    if(attrs.hasAttribute("ended"))
        section.set_ended(to_timepoint(attrs.value("ended").toString()));

    ////////////////////
    // check closing tag
    reader.readElementText();

    if(reader.tokenType() != QXmlStreamReader::EndElement
    || reader.name() != "section")
    throw XmlError("Expecting section end element");

    return section;
}

////////////////////////////////////////////////////////////////////////////////
Section::Duration SectionReader::to_duration(const QString& string)
{
    std::tm tm { };

    std::stringstream ss(string.toLatin1().data());
    ss >> std::get_time(&tm, "%X");

    if(ss.fail()) throw XmlError("Invalid duration");

    using namespace std::chrono;
    return hours(tm.tm_hour) + minutes(tm.tm_min) + seconds(tm.tm_sec);
}

////////////////////////////////////////////////////////////////////////////////
Section::Timepoint SectionReader::to_timepoint(const QString& string)
{
    std::tm tm { };

    std::stringstream ss(string.toLatin1().data());
    ss >> std::get_time(&tm, "%c");

    if(ss.fail()) throw XmlError("Invalid date/time");

    return Section::Clock::from_time_t(std::mktime(&tm));
}
