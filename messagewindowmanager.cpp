#include "messagewindowmanager.h"



MessageWindowManager::MessageWindowManager(AppServer *server, QObject *parent):
    QObject(parent),server(server)
{

}

void MessageWindowManager::openWindow(QString number, QStringList * logs)
{
    if(!activeWindows.count(number.toStdString())){
        MessageWindow * win = new MessageWindow(number,logs);
        connect(win,&MessageWindow::sendMessage,server,&AppServer::writeSocket);
        connect(win,&MessageWindow::closeWindow,this,&MessageWindowManager::closeWindow);
        win->show();
        activeWindows.insert(std::make_pair(number.toStdString(),win));
    }else{
        activeWindows.at(number.toStdString())->activateWindow();
    }

}

void MessageWindowManager::updateWindows()
{
    for(auto i: activeWindows){
        i.second->updateMessages();
    }
}

void MessageWindowManager::closeWindow(QString number)
{
    activeWindows.erase(number.toStdString());
}
