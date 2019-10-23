#include "mainwindow.h"

#include <QApplication>
#include "popup.h"
#include "notipanel.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    for(int i = 0; i< 10 ; i++){
//        Popup * s = new Popup(nullptr);
//        s->displayMessage();
//    }

    //w.show();
    return a.exec();
}
