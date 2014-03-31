#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QDebug>
#include <QRegExp>
#include <QByteArray>

class EchoServer : public QObject{
    Q_OBJECT

private:
    QTcpServer* server;
    QTcpSocket* clientSocket;
    int port;
    bool serverStatus;

public:
    EchoServer(qint16 port, QObject *parent = 0);
    ~EchoServer();
    bool isRunning() const;
    int getPort() const;
    void setPort(int port);
    void start();
    void stop();

public slots:
    void createNewClient();
    void makeEcho();
};

#endif // ECHOSERVER_H
