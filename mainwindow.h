#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include "dialog.h"
#include <QNetworkInterface>
#include "appserver.h"
#include <QThread>
#include "notipanel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void activated(QSystemTrayIcon::ActivationReason reason);
    void connectServer();
    void quitApp();
    void readServerData(QByteArray);
    void openMessageWindow(MessageWidget *); //TODO: get Messages from cache or storage and display them in a window.

public:
    MainWindow();
    ~MainWindow();

private:
    QString IP_ADDRESS ="127.0.0.1";
    quint16 PORT = 8080;
    void setupContextMenu();
    void setupActions();
    void setupConnections();
    void readSavedData();
    void writeSavedData();
    void getIPAddress();


    Dialog * settingsDialog;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    AppServer * appServer;
    QThread * appThread;
    NotiPanel * notiPanel;
    QAction * openSettings;
    QAction * quit;
    QAction * disconnect;
    QAction * notifications;

};
#endif // MAINWINDOW_H
