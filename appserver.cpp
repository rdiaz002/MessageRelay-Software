#include "appserver.h"

AppServer::AppServer(QHostAddress * address, quint16 port, QObject *parent) :address(address),port(port),QObject(parent)
{
    client=nullptr;
    host= new QTcpServer(this);
    host->setMaxPendingConnections(1);
    connect(host,&QTcpServer::newConnection,this,&AppServer::getSocket);
}

void AppServer::startServer()
{
    if(!host->listen(*address,port)){
        emit errorListening();
    }

}

void AppServer::endServer()
{
    if(client!=nullptr){
        client->close(); 
        client->deleteLater();
    }
    host->close();


}

void AppServer::getSocket()
{
    qDebug()<<"Socket Connected";
    client=host->nextPendingConnection();
    host->close();
    connect(client,&QTcpSocket::disconnected,this,&AppServer::socketDisconnected);
    connect(client,&QTcpSocket::readyRead,this,&AppServer::readSocket);
}

void AppServer::socketDisconnected()
{

    qDebug()<<"Socket disconnected";
    disconnect(client,&QTcpSocket::disconnected,this,&AppServer::socketDisconnected);
    disconnect(client,&QTcpSocket::readyRead,this,&AppServer::readSocket);
    client->deleteLater();
    client= nullptr;
    host->listen(*address,port);


}

void AppServer::readSocket()
{
    qDebug()<<"Socket Reading";
    QByteArray data = client->readAll();
    qDebug()<<data;
    emit receivedData(data);
}

