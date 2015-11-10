////////////////////////////////////////////////////////////////////////////////
#include "eventreader.hpp"
#include "sectionreader.hpp"
#include "error.hpp"

#include <QDate>
#include <QString>

////////////////////////////////////////////////////////////////////////////////
static inline QDate to_date(const QString& string)
{
    return QDate::fromString(string, "MMM d yyyy");
}

////////////////////////////////////////////////////////////////////////////////
static inline QString value(const QXmlStreamAttributes& attrs, const QString& name)
{
    return attrs.value(name).toString();
}

////////////////////////////////////////////////////////////////////////////////
Event EventReader::read(QXmlStreamReader& reader)
{
    ////////////////////
    // Event format:
    //   <event name="foo">
    //     <section name="bar" duration="x:xx:xx"/>
    //     ...
    //   </event>

    ////////////////////
    // fast forward until opening tag
    if(reader.tokenType() != QXmlStreamReader::StartElement)
        reader.readNextStartElement();

    ////////////////////
    // check opening tag
    if(reader.tokenType() != QXmlStreamReader::StartElement
    || reader.name() != "event")
    throw XmlError("Expecting event start element");

    ////////////////////
    // get event name
    Event event;
    auto attrs = reader.attributes();

    if(!attrs.hasAttribute("name")) throw XmlError("Missing name attribute");
    event.set_name(value(attrs, "name"));

    if(!attrs.hasAttribute("date")) throw XmlError("Missing date attribute");
    event.set_date(to_date(value(attrs, "name")));

    ////////////////////
    // read sections
    while(reader.readNextStartElement())
        event.insert(SectionReader::read(reader));

    ////////////////////
    // check closing tag
    reader.readElementText();

    if(reader.tokenType() != QXmlStreamReader::EndElement
    || reader.name() != "event")
    throw XmlError("Expecting event end element");

    return event;
}
