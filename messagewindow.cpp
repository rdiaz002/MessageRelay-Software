#include "messagewindow.h"
#include "ui_messagewindow.h"
#include<QDebug>
#include<QLabel>

//TODO: Update Message Window Styling.

MessageWindow::MessageWindow(QString num,QStringList * msgList,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageWindow),
    number(num),
    msgList(msgList)
{
    ui->setupUi(this);
    ui->chatBox->setAlignment(Qt::AlignTop);
    ui->chatBox->setSizeConstraint(QLayout::SetMinimumSize);
    vert = ui->scrollArea->verticalScrollBar();
    connect(vert,&QAbstractSlider::rangeChanged,this,&MessageWindow::slideChange);
    updateMessages();
}



MessageWindow::~MessageWindow()
{
    delete ui;
}

void MessageWindow::updateMessages()
{

    QLayoutItem *child;
    while ((child = ui->chatBox->takeAt(0)) != nullptr) {
        ui->chatBox->removeWidget(child->widget());
        delete child->widget();
        delete child;
    }

    for(auto i : *msgList){
        QLabel * msg = new QLabel(i);
        msg->setAlignment(Qt::AlignLeft);
        msg->setWordWrap(true);
        msg->setContentsMargins(0,10,0,10);
        msg->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::MinimumExpanding);
        msg->setMaximumWidth(100);
        msg->adjustSize();
        ui->chatBox->addWidget(msg);
    }


}

void MessageWindow::on_sendButton_clicked()
{
    //TODO: add the sending protocol to communicate with client app.
    QString msg= ui->textBox->toPlainText();
    msgList->push_back(msg);
    QByteArray data;
    data+=this->number;
    data+=0x02;
    data+=msg;
    data+='\n';
    emit sendMessage(data);
    updateMessages();
}

void MessageWindow::slideChange(int, int)
{
    vert->setValue(vert->maximum());
}

void MessageWindow::on_MessageWindow_finished(int result)
{
    emit closeWindow(number);
}
