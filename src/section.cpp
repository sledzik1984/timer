////////////////////////////////////////////////////////////////////////////////
#include "section.hpp"

#include <QTime>

////////////////////////////////////////////////////////////////////////////////
void Section::read(QXmlStreamReader& reader)
{
    ////////////////////
    // format: <section name="foo" duration="x:xx:xx"/>

    ////////////////////
    // the reader should already be positioned on
    // the section element
    if(reader.tokenType() != QXmlStreamReader::StartElement || reader.name() != "section")
        throw QString("Expecting section start element");

    ////////////////////
    auto attributes = reader.attributes();

    if(!attributes.hasAttribute("name")) throw QString("Missing name attribute");
    set_name(attributes.value("name").toString());

    if(!attributes.hasAttribute("time")) throw QString("Missing time attribute");
    set_time(QTime::fromString(attributes.value("time").toString(), "h:mm:ss"));

    if(!time().isValid()) throw QString("Invalid time attribute");

    ////////////////////
    reader.readElementText();

    if(reader.tokenType() != QXmlStreamReader::EndElement || reader.name() != "section")
        throw QString("Expecting section end element");
}

////////////////////////////////////////////////////////////////////////////////
void Section::write(QXmlStreamWriter& writer) const
{
    writer.writeStartElement("section");
    writer.writeAttribute("name", name());
    writer.writeAttribute("time", time().toString("h:mm:ss"));
    writer.writeEndElement();
}
