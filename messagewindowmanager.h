#ifndef MESSAGEWINDOWMANAGER_H
#define MESSAGEWINDOWMANAGER_H

#include <QObject>

class MessageWindowManager : public QObject
{
    Q_OBJECT
public:
    explicit MessageWindowManager(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MESSAGEWINDOWMANAGER_H
