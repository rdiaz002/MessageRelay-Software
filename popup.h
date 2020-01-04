#ifndef POPUP_H
#define POPUP_H

#include <QDialog>

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
  void showEvent(QShowEvent *) override;
  void mousePressEvent(QMouseEvent *) override;
  ~Popup();

public slots:
  void mClose();

private:
  Ui::Popup *ui;
  void autoPos();
};

#endif // POPUP_H
