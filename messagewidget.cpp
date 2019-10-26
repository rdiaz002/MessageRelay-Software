#include "messagewidget.h"
#include "ui_messagewidget.h"
#include "messageutils.h"
#include <QDebug>
unsigned int MessageWidget::id = 0;

MessageWidget::MessageWidget(QWidget *parent,QString number, QString message) :
    QFrame(parent),
    ui(new Ui::MessageWidget)
{
    ui->setupUi(this);
    ui->number->setText(number);
    ui->Message->setText(message);
    data = {number,message,id++};
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

