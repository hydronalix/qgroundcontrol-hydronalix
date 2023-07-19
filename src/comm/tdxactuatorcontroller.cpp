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
        ///todo
    }
}

void TdxActuatorController::changeTdxState()
{
    _state ^= 1;
    _jobject[_keyword] = _state;
    QJsonDocument doc(_jobject);
    int success = _udpSocket->writeDatagram(
                doc.toJson(QJsonDocument::Compact),
                QHostAddress("192.168.228.69"),
                8888
                );
    qInfo("success was %d", success);
}
