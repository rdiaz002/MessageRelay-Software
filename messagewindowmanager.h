#ifndef MESSAGEWINDOWMANAGER_H
#define MESSAGEWINDOWMANAGER_H

#include <QObject>
#include "messagewindow.h"
#include <unordered_map>
#include "appserver.h"
class MessageWindowManager : public QObject
{
    Q_OBJECT
public:
    explicit MessageWindowManager(AppServer * server,QObject *parent = nullptr);
    void openWindow(QString number,QStringList * logs);
    void updateWindows();
signals:

public slots:
    void closeWindow(QString number);

private:
    std::unordered_map<std::string,MessageWindow *> activeWindows;
    AppServer * server;
};

#endif // MESSAGEWINDOWMANAGER_H
