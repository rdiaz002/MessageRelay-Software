#include "dialog.h"
#include "ui_dialog.h"
#include <QCloseEvent>
#include <QCheckBox>

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);
  minMsg = new QMessageBox();
  minMsg->setCheckBox(new QCheckBox("Do Not Show This Warning Again", this));
  minMsg->setText("MessageRelay will continue to run in the background. Right "
                  "click on the tray icon and click on quit to close "
                  "MessageRelay");
  minMsg->setStandardButtons(QMessageBox::StandardButton::Ok);
}

Dialog::~Dialog() {
  delete ui;
  delete minMsg;
}

void Dialog::setPortText(QString port) { ui->lineEdit_2->setText(port); }

void Dialog::setIPText(QString ip) { ui->label_3->setText(ip); }

void Dialog::closeEvent(QCloseEvent *event) {
  this->hide();
  if (!minMsg->checkBox()->isChecked()) {
    minMsg->exec();
  }
  event->ignore();
}

void Dialog::disconnectedServer() { ui->pushButton->setText("Connect"); }

void Dialog::connectedServer() { ui->pushButton->setText("Disconnect"); }

void Dialog::on_pushButton_clicked() {
  if (ui->pushButton->text().compare("Disconnect") == 0) {
    emit disconnectServer();
  } else {
    emit connectServer();
  }
}
