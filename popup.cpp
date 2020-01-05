#include "popup.h"
#include "ui_popup.h"
#include <QTimer>
#include <QDesktopWidget>
#include <QCloseEvent>
#include <QScreen>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QDebug>
Popup::Popup(QWidget *) : QDialog(nullptr), ui(new Ui::Popup) {

  ui->setupUi(this);
  setStyleSheet("background-color:#ffffff");
  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint |
                 Qt::WindowStaysOnTopHint);
  ui->body->setText("BIG CHONGUS");
  this->adjustSize();
  this->autoPos();
  qDebug() << Ui::windowCount << '\n';
  anim1 = new QPropertyAnimation(this, "geometry");
  anim1->setDuration(250);
  anim1->setStartValue(
      QRect(this->x() + this->width(), this->y(), 0, this->height()));
  anim1->setEndValue(
      QRect(this->x(), this->y(), this->width(), this->height()));

  anim2 = new QPropertyAnimation(this, "windowOpacity");
  anim2->setDuration(2000);
  anim2->setStartValue(1.0);
  anim2->setEndValue(0.0);
  connect(anim2, &QPropertyAnimation::finished, this, &Popup::mClose);

  group = new QSequentialAnimationGroup;
  group->addAnimation(anim1);
  group->addPause(2750);
  group->addAnimation(anim2);
}
void Popup::autoPos() {
  auto desktopRect = QGuiApplication::screens().front()->geometry();
  auto h_max = Ui::windowCount * (desktopRect.height() / this->height() + 5);
  int x, y;
  x = desktopRect.width() - (this->width());
  y = h_max;
  this->move(x, y);
}
void Popup::closeEvent(QCloseEvent *e) { e->accept(); }

void Popup::displayMessage() {
  // TODO: Change this single shot to a custom animation class that will allow
  // users to keep dialog open if mouse is hovering over it.
  Ui::windowCount++;
  this->open();
  group->start(QAbstractAnimation::DeletionPolicy::DeleteWhenStopped);
}

void Popup::mousePressEvent(QMouseEvent *) {
  // hide animation if mouse is clicked on dialog
  this->hide();
  group->stop();
  mClose();
}

Popup::~Popup() { delete ui; }

void Popup::mClose() {
  qDebug() << "Finished";
  Ui::windowCount--;
  this->close();
}
