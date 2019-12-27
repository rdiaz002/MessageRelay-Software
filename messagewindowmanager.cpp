#include "messagewindowmanager.h"



MessageWindowManager::MessageWindowManager(AppServer *server, QObject *parent):
    QObject(parent),server(server)
{

}

void MessageWindowManager::openWindow(QString number, QStringList * logs)
{
    if(!activeWindows.count(number.toStdString())){ //Check if chat window with associated number is active.
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

void MessageWindowManager::updateWindow(QString number)
{
    if(activeWindows.count(number.toStdString())){
        auto activeWindow = activeWindows.at(number.toStdString());
        activeWindow->updateMessages();
        activeWindow->activateWindow();
    }
}

void MessageWindowManager::closeWindow(QString number)
{
    activeWindows.erase(number.toStdString());
}
