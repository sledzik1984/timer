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

    if(!attributes.hasAttribute("duration")) throw "Missing duration attribute";

    QTime time = QTime::fromString(attributes.value("duration").toString(), "h:mm:ss");
    if(!time.isValid()) throw QString("Invalid duration attribute");

    set_duration(std::chrono::seconds(QTime(0, 0).secsTo(time)));

    ////////////////////
    reader.readElementText();

    if(reader.tokenType() != QXmlStreamReader::EndElement || reader.name() != "section")
        throw QString("Expecting section end element");
}

////////////////////////////////////////////////////////////////////////////////
void Section::write(QXmlStreamWriter& writer) const
{
    writer.writeStartElement("section");
    writer.writeAttribute("name", _name);
    writer.writeAttribute("duration", QTime(0, 0).addSecs(_duration.count()).toString("h:mm:ss"));
    writer.writeEndElement();
}
