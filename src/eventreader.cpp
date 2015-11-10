////////////////////////////////////////////////////////////////////////////////
#include "eventreader.hpp"
#include "sectionreader.hpp"
#include "error.hpp"

#include <QString>
#include <QXmlStreamReader>

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
    event.set_date(Event::to_date(value(attrs, "name")));

    ////////////////////
    // read sections
    while(reader.readNextStartElement())
        event._sections.push_back(SectionReader::read(reader));

    ////////////////////
    // check closing tag
    reader.readElementText();

    if(reader.tokenType() != QXmlStreamReader::EndElement
    || reader.name() != "event")
    throw XmlError("Expecting event end element");

    return event;
}
