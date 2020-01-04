#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = nullptr);
  ~Dialog() override;
  void setPortText(QString port);
  void setIPText(QString ip);
  void closeEvent(QCloseEvent *) override;
signals:
  void disconnectServer();
  void connectServer();
public slots:
  void disconnectedServer();
  void connectedServer();
  void on_pushButton_clicked();

private:
  Ui::Dialog *ui;
  QMessageBox *minMsg;
};

#endif // DIALOG_H
