#include "popup.h"
#include "ui_popup.h"
#include <QTimer>
#include <QDesktopWidget>
#include <QCloseEvent>
#include<QScreen>
#include<QPropertyAnimation>
Popup::Popup(QWidget *parent) :
    QDialog(nullptr),
    ui(new Ui::Popup)
{
        ui->setupUi(this);
        setStyleSheet("background-color:#ffffff");
        setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint|Qt::WindowStaysOnTopHint|Qt::Popup);

        //ui->title->setText(title); ui->title->setStyleSheet("color:#300000; font-weight: bold;");
        ui->body->setText("BIG CHONGUS         ");
        this->adjustSize();
       // ui->image->setPixmap(image);



        this->autoPos();
}
void Popup::autoPos()
{
    auto desktopRect = QGuiApplication::screens().front()->geometry();

    auto h_max = desktopRect.height() / this->height();
    int x, y;
    //do {//To do

        x = desktopRect.width() - (3 * this->width());
        //y = this->height() * (NotificationWidgetRecord::GetInstance().LastIdx() % h_max);
        y = this->height();

    //} while ( x < 0);
    this->move(x,y);

}
void Popup::closeEvent(QCloseEvent *e)
{

    e->accept();


}

int Popup::exec()
{
    QTimer::singleShot(5000, this, SLOT(close()));
    QPropertyAnimation an(this,"geometry");
    an.setDuration(10000);
    an.setStartValue(QRect(this->x(),this->y(),10,10));
    an.setEndValue(QRect(this->x(),this->y(),1000,this->y()));
    an.start();
    return QDialog::exec();
}
Popup::~Popup()
{
    delete ui;
}
