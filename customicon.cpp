#include "customicon.h"
#include "ui_customicon.h"
#include <QRect>
#include <QScreen>
CustomIcon::CustomIcon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomIcon)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setGeometry(setDialogLocation());
    this->updateGeometry();
}

CustomIcon::~CustomIcon()
{
    delete ui;
}

QRect CustomIcon::setDialogLocation() // get window size to properly size the
                                 // NotificationPanel.
{
  QScreen *mainScreen = QGuiApplication::screens()[0];
  double screenWidth = static_cast<double>(mainScreen->geometry().width());
  int screenHeight = mainScreen->geometry().height();

  QRect sizeRect;
  sizeRect.moveTo(static_cast<int>(screenWidth) - this->width(),
                  0);

  return sizeRect;
}
