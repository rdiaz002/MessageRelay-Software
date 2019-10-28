#include "messagewindow.h"
#include "ui_messagewindow.h"
#include<QDebug>
#include<QLabel>
MessageWindow::MessageWindow(QStringList * msgList,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageWindow),
    msgList(msgList)
{
    ui->setupUi(this);
    ui->chatBox->setAlignment(Qt::AlignTop);
    for(auto i : *msgList){
        QLabel * msg = new QLabel(i,this->layout()->widget());
        msg->setAlignment(Qt::AlignLeft);
        msg->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
        msg->setContentsMargins(0,10,0,10);
        ui->chatBox->addWidget(msg);
    }
}



MessageWindow::~MessageWindow()
{
    delete ui;
}

void MessageWindow::paintEvent(QPaintEvent * e)
{

    QDialog::paintEvent(e);
}
