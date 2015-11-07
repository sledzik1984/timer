////////////////////////////////////////////////////////////////////////////////
#include "sectionreader.hpp"
#include "xmlerror.hpp"

#include <QXmlStreamReader>

////////////////////////////////////////////////////////////////////////////////
Section SectionReader::read(QXmlStreamReader& reader)
{
    ////////////////////
    // format: <section name="foo" duration="xx:xx:xx"/>
    Section section;

    ////////////////////
    // check opening tag
    if(reader.tokenType() != QXmlStreamReader::StartElement
    || reader.name() != "section")
    throw XmlError("Expecting section start element");

    ////////////////////
    // get section name and duration
    auto attributes = reader.attributes();

    if(!attributes.hasAttribute("name")) throw XmlError("Missing name attribute");
    section.set_name(attributes.value("name").toString());

    if(!attributes.hasAttribute("time")) throw XmlError("Missing time attribute");
    section.set_time(QTime::fromString(attributes.value("time").toString(), "h:mm:ss"));

    if(!section.time().isValid()) throw XmlError("Invalid time attribute");

    ////////////////////
    // check closing tag
    reader.readElementText();

    if(reader.tokenType() != QXmlStreamReader::EndElement
    || reader.name() != "section")
    throw XmlError("Expecting section end element");

     return section;
}
