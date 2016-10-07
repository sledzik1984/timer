////////////////////////////////////////////////////////////////////////////////
#include "oscsource.hpp"

#include <cstring>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
OscSource::OscSource(int port, QObject* parent) :
    QThread(parent),
    socket(IpEndpointName(IpEndpointName::ANY_ADDRESS, port), this)
{
    start();
}

////////////////////////////////////////////////////////////////////////////////
OscSource::~OscSource()
{
    socket.AsynchronousBreak();
    wait();
}

////////////////////////////////////////////////////////////////////////////////
OscSource::Pointer OscSource::instance()
{
    static OscSource::Pointer osc_time(new OscSource());
    return osc_time;
}

////////////////////////////////////////////////////////////////////////////////
void OscSource::ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName&)
{
    try
    {
        QString addr = m.AddressPattern();
        auto args = m.ArgumentStream();

        if(addr == "/channel/1/stage/layer/10/file/path")
        {
            const char* path = nullptr;
            args >> path >> osc::EndMessage;

            if(path) emit path_changed(path);
        }
        else if(addr == "/channel/1/stage/layer/10/file/time")
        {
            float time = -1, total = -1;
            args >> time >> total >> osc::EndMessage;

            if(time >= 0 && total >= 0)
            {
                emit time_changed(QTime(0, 0, 0).addSecs(static_cast<int>(time)),
                                  QTime(0, 0, 0).addSecs(static_cast<int>(total)));
            }
        }
        else if(addr == "/event/status")
        {
            const char* status = nullptr;
            args >> status >> osc::EndMessage;

                 if(0 == std::strcmp(status, "start")) emit status_changed(Start);
            else if(0 == std::strcmp(status, "stop"))  emit status_changed(Stop);
            else if(0 == std::strcmp(status, "reset")) emit status_changed(Reset);
        }
    }
    catch(osc::Exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
