#include "tdxactuatorcontroller.h"

TdxActuatorController::TdxActuatorController(QGCApplication* app, QGCToolbox* toolbox)
    : QGCTool(app, toolbox)
{
    _udpSocket = new QUdpSocket(this);
    _udpSocket->bind(QHostAddress("192.168.228.12"), 5005);

    connect(_udpSocket, &QUdpSocket::readyRead,
         this, &TdxActuatorController::readPendingDatagrams);

    _keyword = "arm";
    _state = 0;
}

void TdxActuatorController::readPendingDatagrams()
{
    while (_udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = _udpSocket->receiveDatagram();
        QJsonObject jobject;
        QJsonDocument doc = QJsonDocument::fromJson(datagram.data());

        /*
         * json parsing checks
         */
        if (!doc.isNull())
        {
            if (doc.isObject())
            {
                jobject = doc.object();
            }
            else
            {
                qInfo("document is not object");
                return;
            }
        }
        else
        {
            qInfo("invalid json");
            return;
        }

        /*
         * re-send desired state if the boat reg value isn't the ground-side state
         * (useful for dropped packets)
         */
        if (jobject.contains("arm"))
        {
            if (jobject["arm"] != _state)
            {
                _sendState();
            }
            else
            {
                return;
            }
        }
        else
        {
            qInfo("jobject does not contain arm key");
            return;
        }
    }
}

void TdxActuatorController::changeTdxState()
{
    _state ^= 1;
    _sendState();
}

void TdxActuatorController::_sendState()
{
    _jobject[_keyword] = _state;
    QJsonDocument doc(_jobject);
    int success = _udpSocket->writeDatagram(
                doc.toJson(QJsonDocument::Compact),
                QHostAddress("192.168.228.69"),
                8888
                );
    qInfo("success was %d", success);
}

int TdxActuatorController::getState()
{
    qInfo("state returned as %d", _state);
    return _state;
}
