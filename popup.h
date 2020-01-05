#ifndef POPUP_H
#define POPUP_H

#include <QDialog>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
namespace Ui {
class Popup;
static int windowCount = 1;
}

class Popup : public QDialog {
  Q_OBJECT

public:
  explicit Popup(QWidget *parent = nullptr);
  void closeEvent(QCloseEvent *) override;
  void displayMessage();
  void mousePressEvent(QMouseEvent *) override;
  ~Popup();

public slots:
  void mClose();

private:
  QPropertyAnimation *anim1;
  QPropertyAnimation *anim2;
  QSequentialAnimationGroup *group;
  Ui::Popup *ui;
  void autoPos();
};

#endif // POPUP_H
