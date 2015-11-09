////////////////////////////////////////////////////////////////////////////////
#ifndef SECTIONWRITER_HPP
#define SECTIONWRITER_HPP

#include "section.hpp"

////////////////////////////////////////////////////////////////////////////////
class QXmlStreamWriter;

////////////////////////////////////////////////////////////////////////////////
class SectionWriter
{
public:
    static void write(QXmlStreamWriter&, const Section&);
};

////////////////////////////////////////////////////////////////////////////////
#endif // SECTIONWRITER_HPP