////////////////////////////////////////////////////////////////////////////////
#ifndef OSCSOURCE_HPP
#define OSCSOURCE_HPP

////////////////////////////////////////////////////////////////////////////////
#include <QMetaType>
#include <QString>
#include <QThread>
#include <QTime>

#include <ip/UdpSocket.h>
#include <osc/OscPacketListener.h>
#include <osc/OscReceivedElements.h>

#include <memory>
#include <utility>

////////////////////////////////////////////////////////////////////////////////
enum Status { Start, Stop, Reset };
Q_DECLARE_METATYPE(Status)

////////////////////////////////////////////////////////////////////////////////
class OscSource : public QThread, public osc::OscPacketListener
{
    Q_OBJECT

public:
    ////////////////////
    using Pointer = std::shared_ptr<OscSource>;

    ////////////////////
    explicit OscSource(int port = 7250, QObject* parent = nullptr);
    virtual ~OscSource() override;

    ////////////////////
    static OscSource::Pointer instance();

signals:
    ////////////////////
    void path_changed(const QString&);
    void time_changed(const QTime& time, const QTime& total);
    void status_changed(Status);

protected:
    ////////////////////
    virtual void run() override { socket.Run(); }

    ////////////////////
    virtual void ProcessMessage(const osc::ReceivedMessage&, const IpEndpointName&) override;

private:
    ////////////////////
    UdpListeningReceiveSocket socket;
};

////////////////////////////////////////////////////////////////////////////////
#endif // OSCSOURCE_HPP
