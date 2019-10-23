#include "notipanel.h"
#include "ui_notipanel.h"
#include <QScreen>
#include <QDesktopWidget>
NotiPanel::NotiPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotiPanel)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint,true);
    this->setWindowFlag(Qt::Popup,true);

    this->setGeometry(setDialogSize());
    this->updateGeometry();
    this->setStyleSheet("#NotiPanel{border: 1px solid black;border-radius: 10px;}");

}

NotiPanel::~NotiPanel()
{
    delete ui;
}

QRect NotiPanel::setDialogSize()
{
    QScreen * mainScreen = QGuiApplication::screens()[0];
    double screenWidth = static_cast<double>(mainScreen->geometry().width());
    int screenHeight = mainScreen->geometry().height();

    QRect sizeRect;
    sizeRect.setWidth(static_cast<int>(screenWidth*0.20));
    sizeRect.setHeight(static_cast<int>(screenHeight*0.90));
    sizeRect.moveTo(static_cast<int>(screenWidth)-sizeRect.width(),static_cast<int>(screenHeight*0.05));



    return sizeRect;
}
