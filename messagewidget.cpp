#include "messagewidget.h"
#include "ui_messagewidget.h"
#include "messageutils.h"
#include <QDebug>
unsigned int MessageWidget::id = 0;

MessageWidget::MessageWidget(MessageItem & item,QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MessageWidget)
{
    ui->setupUi(this);
    ui->number->setText(item.name);
    ui->Message->setText(item.message);
    data = {item.name,item.num,item.message,id++};
}

MessageWidget::~MessageWidget()
{
    delete ui;
}

void MessageWidget::mousePressEvent(QMouseEvent *)
{
    qDebug()<<data.id;
    emit openMessageWindow(this);
}

