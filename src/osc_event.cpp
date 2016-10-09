////////////////////////////////////////////////////////////////////////////////
#include "osc_event.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace Osc
{

////////////////////////////////////////////////////////////////////////////////
Event::Event(QObject* parent) :
    QObject(parent),
    _addr_status("/event/status")
{
    connect(&*Listener::instance(), &Listener::message_received, this, &Event::proc_message);
}

////////////////////////////////////////////////////////////////////////////////
void Event::proc_message(const QString& addr, const QList<QVariant>& args)
{
    if(addr == _addr_status)
    {
        if(args.size() == 1)
        {
            auto status = args.at(0).toString();

                 if(status == "start") emit status_changed(Started);
            else if(status == "stop")  emit status_changed(Stopped);
            else if(status == "reset") emit status_changed(Reset);
        }
        else throw std::runtime_error("invalid video name argument");

    }
}

////////////////////////////////////////////////////////////////////////////////
}
