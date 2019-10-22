#include "mainwindow.h"

#include <QApplication>
#include "popup.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Popup s(nullptr);
    s.exec();

    //w.show();
    return a.exec();
}
