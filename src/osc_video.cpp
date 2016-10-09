////////////////////////////////////////////////////////////////////////////////
#include "osc_video.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace Osc
{

////////////////////////////////////////////////////////////////////////////////
Video::Video(int channel, int layer, QObject* parent) :
    QObject(parent),
    _addr_name(QString("/channel/%1/stage/layer/%2/file/path").arg(channel).arg(layer)),
    _addr_time(QString("/channel/%1/stage/layer/%2/file/time").arg(channel).arg(layer))
{
    connect(&*Listener::instance(), &Listener::message_received, this, &Video::proc_message);
}

////////////////////////////////////////////////////////////////////////////////
void Video::proc_message(const QString& addr, const QList<QVariant>& args)
{
    if(addr == _addr_name)
    {
        if(args.size() == 1)
            emit name_changed(args[0].toString());
    }
    else if(addr == _addr_time)
    {
        if(args.size() == 2)
            emit time_changed(QTime(0, 0, 0).addMSecs(static_cast<int>(1000 * args[0].toFloat())),
                              QTime(0, 0, 0).addMSecs(static_cast<int>(1000 * args[1].toFloat())));
    }
}

////////////////////////////////////////////////////////////////////////////////
}
