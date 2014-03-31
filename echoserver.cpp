#include "echoserver.h"

EchoServer::EchoServer(qint16 port, QObject *parent) :
    QObject(parent),
    port(port){
    server = new QTcpServer(this);
    serverStatus = false;
}

EchoServer::~EchoServer() {
    stop();
}

void EchoServer::stop() {
    clientSocket->close();
    server->close();
}

bool EchoServer::isRunning() const {
    return serverStatus;
}

int EchoServer::getPort() const {
    return port;
}

void EchoServer::setPort(int port) {
    this->port = port;
}

void EchoServer::start() {
    if (serverStatus) {
        return;
    }
    if ( !server->listen(QHostAddress::Any, port) ) {
        qDebug() << "Server could not start!";
        return;
    }
    qDebug() << "Server started!";
    connect(server, SIGNAL(newConnection()),this,SLOT(createNewClient()));
    serverStatus = true;
}

void EchoServer::createNewClient() {
    clientSocket = server->nextPendingConnection();
    connect(clientSocket, SIGNAL(readyRead()),this,SLOT(makeEcho()));
}

void EchoServer::makeEcho() {
    clientSocket->write(clientSocket->readAll());
}
