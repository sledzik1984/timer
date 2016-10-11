////////////////////////////////////////////////////////////////////////////////
#include "osc_listener.hpp"

#include <QByteArray>
#include <QString>

////////////////////////////////////////////////////////////////////////////////
namespace Osc
{


////////////////////////////////////////////////////////////////////////////////
Listener::Listener(QObject* parent) :
    QThread(parent),
    _socket(IpEndpointName(7250), this)
{
    start();
}

////////////////////////////////////////////////////////////////////////////////
Listener::~Listener()
{
    _socket.AsynchronousBreak();
    wait();
}

////////////////////////////////////////////////////////////////////////////////
Listener::Pointer Listener::instance()
{
    static Listener::Pointer listener(new Listener());
    return listener;
}

////////////////////////////////////////////////////////////////////////////////
void Listener::ProcessMessage(const osc::ReceivedMessage& message, const IpEndpointName&)
{
    QString addr = message.AddressPattern();
    QList<QVariant> args;

    for(auto ri = message.ArgumentsBegin(), ri_end = message.ArgumentsEnd(); ri != ri_end; ++ri)
    {
        switch(ri->TypeTag())
        {
        case osc::TRUE_TYPE_TAG:
        case osc::FALSE_TYPE_TAG:
            args.append(ri->AsBool());
            break;
        case osc::NIL_TYPE_TAG:
            args.append(QVariant());
            break;
        case osc::INT32_TYPE_TAG:
            args.append(QVariant::fromValue<osc::int32>(ri->AsInt32()));
            break;
        case osc::FLOAT_TYPE_TAG:
            args.append(ri->AsFloat());
            break;
        case osc::CHAR_TYPE_TAG:
            args.append(ri->AsChar());
            break;
        case osc::RGBA_COLOR_TYPE_TAG:
            args.append(QVariant::fromValue<osc::uint32>(ri->AsRgbaColor()));
            break;
        case osc::MIDI_MESSAGE_TYPE_TAG:
            args.append(QVariant::fromValue<osc::uint32>(ri->AsMidiMessage()));
            break;
        case osc::INT64_TYPE_TAG:
            args.append(QVariant::fromValue<osc::int64>(ri->AsInt64()));
            break;
        case osc::TIME_TAG_TYPE_TAG:
            args.append(QVariant::fromValue<osc::uint64>(ri->AsTimeTag()));
            break;
        case osc::DOUBLE_TYPE_TAG:
            args.append(ri->AsDouble());
            break;
        case osc::STRING_TYPE_TAG:
            args.append(QString(ri->AsString()));
            break;
        case osc::SYMBOL_TYPE_TAG:
            args.append(QString(ri->AsSymbol()));
            break;
        case osc::BLOB_TYPE_TAG:
            {
                const void* value;
                osc::osc_bundle_element_size_t size;
                ri->AsBlob(value, size);

                args.append(QByteArray(static_cast<const char*>(value), size));
            }
            break;
        }
    }

    emit message_received(addr, args);
}

////////////////////////////////////////////////////////////////////////////////
}
