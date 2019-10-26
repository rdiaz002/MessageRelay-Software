#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QIcon>
#include <messageutils.h>


void MainWindow::activated(QSystemTrayIcon::ActivationReason reason)
{
    qDebug()<<reason;
}

void MainWindow::connectServer()
{
    appThread->start();
}

void MainWindow::quitApp()
{
    writeSavedData();
    QApplication::quit();
}

void MainWindow::readServerData(QByteArray data)
{
    int num_index= data.indexOf(0x02);
    int msg_index= data.indexOf(0x03);
    trayIcon->showMessage(data.left(num_index),data.mid(num_index+1,(msg_index-num_index)-1),QIcon());

    MessageItem msg;
    msg.num=data.left(num_index);
    msg.message =data.mid(num_index+1,(msg_index-num_index)-1);
    (*notiPanel) << msg;

}

MainWindow::MainWindow()
{

    QApplication::setQuitOnLastWindowClosed(false);

    readSavedData();
    getIPAddress();
    appServer = new AppServer(new QHostAddress(IP_ADDRESS),PORT);
    appThread = new QThread(this);

    settingsDialog = new Dialog(this);
    settingsDialog->setIPText(IP_ADDRESS);
    settingsDialog->setPortText(QVariant(PORT).toString());

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icons/noun_signal.svg"));

    notiPanel = new NotiPanel;

    setupContextMenu();
    setupConnections();

    appServer->moveToThread(appThread);
    trayIcon->show();
    appThread->start();



}

MainWindow::~MainWindow()
{
    delete openSettings;
    delete quit;
    delete disconnect;
    delete settingsDialog;
}

void MainWindow::setupContextMenu()
{
    trayIconMenu = new QMenu(this);
    setupActions();
    trayIcon->setContextMenu(trayIconMenu);
}



void MainWindow::setupActions()
{
    openSettings = new QAction("Open",this);
    connect(openSettings,&QAction::triggered,settingsDialog,&Dialog::show);

    quit = new QAction("Quit",this);
    connect(quit,&QAction::triggered,this,&MainWindow::quitApp);

    disconnect = new QAction("Disconnect",this);
    connect(disconnect,&QAction::triggered,appThread,&QThread::quit);

    notifications = new QAction("Notifications",this);
    connect(notifications,&QAction::triggered,notiPanel,&NotiPanel::show);

    trayIconMenu->addAction(notifications);
    trayIconMenu->addAction(openSettings);
    trayIconMenu->addAction(disconnect);
    trayIconMenu->addAction(quit);


}

void MainWindow::setupConnections()
{
    connect(appThread,SIGNAL(started()),appServer,SLOT(startServer()));
    connect(appThread,SIGNAL(started()),settingsDialog,SLOT(connectedServer()));
    connect(appThread,SIGNAL(finished()),appServer,SLOT(endServer()));
    connect(appThread,SIGNAL(finished()),settingsDialog,SLOT(disconnectedServer()));
    connect(appServer,SIGNAL(errorListening()),settingsDialog,SLOT(disconnectedServer()));
    connect(appServer,&AppServer::receivedData,this,&MainWindow::readServerData);
    connect(appServer,SIGNAL(errorListening()),appThread,SLOT(quit()));
    connect(quit,SIGNAL(triggered()),appThread,SLOT(quit()));
    connect(settingsDialog,&Dialog::connectServer,this,&MainWindow::connectServer);
    connect(settingsDialog,&Dialog::disconnectServer,appThread,&QThread::quit);
    connect(notiPanel,&NotiPanel::openMessageWindow,this,&MainWindow::openMessageWindow);
}


void MainWindow::readSavedData()
{
    QSettings savedData(QSettings::IniFormat,QSettings::UserScope,"ThisUs","MessageRelay");
    if(savedData.contains("Server_ip")){
        IP_ADDRESS = savedData.value("Server_ip").toString();
    }else{
        savedData.setValue("Server_ip","127.0.0.1");
    }
    if(savedData.contains("Server_port")){
        PORT = savedData.value("Server_port").toInt();
    }else{
        savedData.setValue("Server_port","8080");
    }


}

void MainWindow::writeSavedData()
{
    QSettings savedData(QSettings::IniFormat,QSettings::UserScope,"ThisUs","MessageRelay");
    savedData.setValue("Server_ip",IP_ADDRESS);
    savedData.setValue("Server_port",PORT);
}

void MainWindow::getIPAddress()
{
    QNetworkInterface inter;
    for(auto intface: inter.allInterfaces())
    {

        if (intface.flags().testFlag(QNetworkInterface::IsUp) && !intface.flags().testFlag(QNetworkInterface::IsLoopBack))
            foreach (QNetworkAddressEntry entry, intface.addressEntries())
            {
            if ( intface.hardwareAddress() != "00:00:00:00:00:00" && entry.ip().toString().contains(".") && !intface.humanReadableName().contains("VirtualBox"))
               IP_ADDRESS=entry.ip().toString();
            }
    }
}

void MainWindow::openMessageWindow(MessageWidget * item)
{
    delete item;
}

