#ifndef APPSERVER_H
#define APPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
class AppServer : public QObject {
  Q_OBJECT
public:
  explicit AppServer(QHostAddress *, quint16 port, QObject *parent = nullptr);

signals:
  void errorListening();
  void receivedData(QByteArray);
public slots:
  void startServer();
  void endServer();
  void getSocket();
  void socketDisconnected();
  void readSocket();
  void writeSocket(QByteArray);

private:
  QHostAddress *address;
  quint16 port;
  QTcpServer *host;
  QTcpSocket *client;
};

#endif // APPSERVER_H
