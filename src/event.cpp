////////////////////////////////////////////////////////////////////////////////
#include "event.hpp"

////////////////////////////////////////////////////////////////////////////////
void Event::clear()
{
    _name.clear();
    _sections.clear();
}

////////////////////////////////////////////////////////////////////////////////
void Event::read(QXmlStreamReader& reader)
{
    clear();

    ////////////////////
    // format: <event name="foo">
    //           <section name="bar" duration="x:xx:xx"/>
    //           <section name="baz" duration="x:xx:xx"/>
    //           ...
    //         </event>

    try
    {
        ////////////////////
        // the reader should already be positioned on
        // the event element
        if(reader.tokenType() != QXmlStreamReader::StartElement || reader.name() != "event")
            throw "Expecting event start element";

        ////////////////////
        auto attributes = reader.attributes();

        if(!attributes.hasAttribute("name")) throw "Missing name attribute";
        set_name(attributes.value("name").toString());

        ////////////////////
        while(reader.readNextStartElement())
        {
            Section section;
            section.read(reader);

            _sections.push_back(std::move(section));
        }

        if(reader.tokenType() != QXmlStreamReader::EndElement || reader.name() != "event")
            throw "Expecting event end element";
    }
    catch(const char* e)
    {
        reader.raiseError(e);
    }
}

////////////////////////////////////////////////////////////////////////////////
void Event::write(QXmlStreamWriter& writer) const
{
    writer.writeStartElement("event");
    writer.writeAttribute("name", _name);
    for(const Section& section: _sections) section.write(writer);
    writer.writeEndElement();
}
