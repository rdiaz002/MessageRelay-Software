#include "customicon.h"
#include "ui_customicon.h"

CustomIcon::CustomIcon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomIcon)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlag(Qt::FramelessWindowHint);
}

CustomIcon::~CustomIcon()
{
    delete ui;
}
