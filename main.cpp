#include "mainwindow.h"

#include <QApplication>
#include "popup.h"
#include "notipanel.h"
#include "messagewindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //Testing new message Window
//    QStringList * msgList = new QStringList{"Hello","GOOdbye","Voog","GOOdbye","Voog","GOOdbye","Voog","GOOdbye","Voog","GOOdbye","Voog","GOOdbye","Voog","GOOdbye","Voog","GOOdbye","Voog","GOOdbye","Voog","GOOdbye","Voog"};
//    MessageWindow temp(msgList,nullptr);
//    temp.show();


    //w.show();

    return a.exec();
}
