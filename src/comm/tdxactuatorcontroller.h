#ifndef TDXACTUATORCONTROLLER_H
#define TDXACTUATORCONTROLLER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QJsonObject>
#include <QJsonDocument>
#include <QGCToolbox.h>

class TdxActuatorController : public QGCTool
{
    Q_OBJECT

public:
    TdxActuatorController(QGCApplication* app, QGCToolbox* toolbox);

    Q_INVOKABLE void    changeTdxState();
    Q_INVOKABLE void    readPendingDatagrams();
    Q_INVOKABLE int     getState();

private:
    QUdpSocket*     _udpSocket;
    int             _state;
    QString         _keyword;
    QJsonObject     _jobject;
    void            _sendState();

signals:
};

#endif // TDXACTUATORCONTROLLER_H
