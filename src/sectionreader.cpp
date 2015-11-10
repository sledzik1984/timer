////////////////////////////////////////////////////////////////////////////////
#include "sectionreader.hpp"
#include "error.hpp"

#include <QDateTime>
#include <QString>
#include <QTime>

////////////////////////////////////////////////////////////////////////////////
static inline Duration to_duration(const QString& string)
{
    return QTime(0, 0).secsTo(QTime::fromString(string, "H:mm:ss"));
}

////////////////////////////////////////////////////////////////////////////////
static inline QDateTime to_datetime(const QString& string)
{
    return QDateTime::fromString(string, "MMM d h:mm:ss yyyy");
}

////////////////////////////////////////////////////////////////////////////////
static inline QString value(const QXmlStreamAttributes& attrs, const QString& name)
{
    return attrs.value(name).toString();
}

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

    if(!attrs.hasAttribute("name")) throw XmlError("Missing name attribute");
    section.set_name(value(attrs, "name"));

    if(!attrs.hasAttribute("duration")) throw XmlError("Missing duration attribute");
    section.set_duration(to_duration(value(attrs, "duration")));

    if(attrs.hasAttribute("started"))
        section.set_started(to_datetime(value(attrs, "started")));

    if(attrs.hasAttribute("ended"))
        section.set_ended(to_datetime(value(attrs, "ended")));

    ////////////////////
    // check closing tag
    reader.readElementText();

    if(reader.tokenType() != QXmlStreamReader::EndElement
    || reader.name() != "section")
    throw XmlError("Expecting section end element");

    return section;
}
