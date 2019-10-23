#include "popup.h"
#include "ui_popup.h"
#include <QTimer>
#include <QDesktopWidget>
#include <QCloseEvent>
#include<QScreen>
#include<QPropertyAnimation>
#include <QDebug>
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
        qDebug()<<Ui::windowCount<<'\n';
}
void Popup::autoPos()
{
    auto desktopRect = QGuiApplication::screens().front()->geometry();

    auto h_max = Ui::windowCount*(desktopRect.height() / this->height());
    int x, y;
    //do {//To do

        x = desktopRect.width() - (3 * this->width());
        //y = this->height() * (NotificationWidgetRecord::GetInstance().LastIdx() % h_max);
        y = h_max;

    //} while ( x < 0);
    this->move(x,h_max);

}
void Popup::closeEvent(QCloseEvent *e)
{

    e->accept();


}

void Popup::displayMessage()
{   QTimer::singleShot(5000, this, SLOT(mClose()));
    Ui::windowCount++;
    this->open();
}

void Popup::showEvent(QShowEvent *)
{
    QPropertyAnimation * an = new QPropertyAnimation(this,"windowOpacity");
    an->setDuration(5000);
    an->setStartValue(1.0);
    an->setEndValue(0.0);
    an->start(QAbstractAnimation::DeleteWhenStopped);
}
Popup::~Popup()
{
    delete ui;
}

void Popup::mClose()
{
    Ui::windowCount--;
    this->close();
}
