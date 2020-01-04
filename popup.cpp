#include "popup.h"
#include "ui_popup.h"
#include <QTimer>
#include <QDesktopWidget>
#include <QCloseEvent>
#include <QScreen>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QDebug>
Popup::Popup(QWidget *parent) : QDialog(nullptr), ui(new Ui::Popup) {

  ui->setupUi(this);
  setStyleSheet("background-color:#ffffff");
  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint |
                 Qt::WindowStaysOnTopHint);
  ui->body->setText("BIG CHONGUS");
  this->adjustSize();
  this->autoPos();
  qDebug() << Ui::windowCount << '\n';
}
void Popup::autoPos() {
  auto desktopRect = QGuiApplication::screens().front()->geometry();

  auto h_max = Ui::windowCount * (desktopRect.height() / this->height() + 5);
  int x, y;
  x = desktopRect.width() - (this->width());
  y = h_max;
  this->move(x, h_max);
}
void Popup::closeEvent(QCloseEvent *e) { e->accept(); }

void Popup::displayMessage() {
  // TODO: Change this single shot to a custom animation class that will allow
  // users to keep dialog open if mouse is hovering over it.
  QTimer::singleShot(5000, this, SLOT(mClose()));
  Ui::windowCount++;
  this->open();
}

void Popup::showEvent(QShowEvent *) {
  // save animations to control start, stop, and rewind functions.
  QPropertyAnimation *an1 = new QPropertyAnimation(this, "geometry");
  an1->setDuration(250);
  an1->setStartValue(
      QRect(this->x() + this->width(), this->y(), 0, this->height()));
  an1->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
  QPropertyAnimation *an = new QPropertyAnimation(this, "windowOpacity");
  an->setDuration(2000);
  an->setStartValue(1.0);
  an->setEndValue(0.0);

  QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
  group->addAnimation(an1);
  group->addPause(2750);
  group->addAnimation(an);
  group->start(QAbstractAnimation::DeletionPolicy::DeleteWhenStopped);
}

void Popup::mousePressEvent(QMouseEvent *) {
  // hide animation if mouse is clicked on dialog
  this->hide();
  qDebug() << this->windowTitle();
}
Popup::~Popup() { delete ui; }

void Popup::mClose() {

  Ui::windowCount--;
  this->close();
}
