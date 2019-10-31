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
    msgList->push_back("Ronny TOo many spaces breaks TOo many spaces breaks TOo many spaces breaks TOo many spaces breaks TOo many spaces breaks TOo many spaces breaks TOo many spaces breaks");
    updateMessages();
}

void MessageWindow::slideChange(int, int)
{
    vert->setValue(vert->maximum());
}
