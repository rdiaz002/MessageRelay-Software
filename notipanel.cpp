#include "notipanel.h"
#include "ui_notipanel.h"
#include <QScreen>
#include <QDesktopWidget>
#include <QLabel>
#include <QString>
#include "messagewidget.h"
#include "messagewidget.h"
#include <QDebug>

NotiPanel::NotiPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotiPanel)
{
    ui->setupUi(this);
    notifications = new std::unordered_set<MessageWidget *>;

    //Test Samples
    this->operator<<({QString("Hell"),QString("Hi"),0});
    this->operator<<({QString("Hell"),QString("Hi2"),0});
    this->operator<<({QString("Hell"),QString("Hi"),0});
    this->operator<<({QString("Hell"),QString("Hi2"),0});

    ui->verticalLayout->setAlignment(Qt::AlignTop);
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

void NotiPanel::notificationClicked(MessageWidget * item) //When notification is clicked remove it from the layout and delete it from the notification list.
{
    ui->verticalLayout->removeWidget(item);
    notifications->erase(item);
    emit openMessageWindow(item);
}

QRect NotiPanel::setDialogSize() //get window size to properly size the NotificationPanel.
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

void NotiPanel::operator<<(MessageItem item) //Create a new MessageWidget and add it to the NotificationList and Layout.
{

    MessageWidget * temp = new MessageWidget(this,item.num,item.message);
    notifications->insert(temp);
    ui->verticalLayout->addWidget(temp);
    connect(temp,&MessageWidget::openMessageWindow,this,&NotiPanel::notificationClicked);

}
