////////////////////////////////////////////////////////////////////////////////
#include "eventreader.hpp"
#include "sectionreader.hpp"
#include "xmlerror.hpp"

#include <QXmlStreamReader>

////////////////////////////////////////////////////////////////////////////////
Event EventReader::read(QXmlStreamReader& reader)
{
    ////////////////////
    // Event format:
    //   <event name="foo">
    //     <section name="bar" duration="x:xx:xx"/>
    //     ...
    //   </event>
    Event event;

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
    auto attributes = reader.attributes();

    if(!attributes.hasAttribute("name")) throw XmlError("Missing name attribute");
    event.set_name(attributes.value("name").toString());

    ////////////////////
    // read sections
    while(reader.readNextStartElement())
        event.push_back(SectionReader::read(reader));

    ////////////////////
    // check closing tag
    reader.readElementText();

    if(reader.tokenType() != QXmlStreamReader::EndElement
    || reader.name() != "event")
    throw XmlError("Expecting event end element");

    return event;
}
